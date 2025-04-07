#include "AControlServoActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include <Windows.h>

AControlServoActor::AControlServoActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AControlServoActor::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ObsucreaOneTest_1"), FoundActors);

    if (FoundActors.Num() > 0)
    {
        AActor* Actor = FoundActors[0];
        if (Actor)
        {
            // Ensure this is actually the correct type (AActor)
            if (Actor->IsA(AActor::StaticClass()))
            {
                USkeletalMeshComponent* SkeletalMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();
                if (SkeletalMesh)
                {
                    if (SkeletalMesh->GetName() == TEXT("ObsucreaOneTest"))
                    {
                        AttachToSkeletalMesh(SkeletalMesh);
                        UE_LOG(LogTemp, Log, TEXT("Successfully attached to skeletal mesh: %s"), *SkeletalMesh->GetName());
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Incorrect skeletal mesh name!"));
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found on actor: %s"), *Actor->GetName());
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Found actor is not of the expected type!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Actor is null!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Actor ObsucreaOneTest_1 not found!"));
    }

    if (!IsPortAvailable(PortName) || !OpenSerialPort())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize serial communication on port: %s"), *PortName);
        return;
    }

    InitializeServoPositions();
}

void AControlServoActor::AttachToSkeletalMesh(USkeletalMeshComponent* SkeletalMesh)
{
    AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void AControlServoActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateServoPositionsFromAnimation();
}

void AControlServoActor::UpdateServoPositionsFromAnimation()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ObsucreaOneTest_1"), FoundActors);

    if (FoundActors.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Actor with tag 'ObsucreaOneTest_1' not found!"));
        return;
    }

    AActor* Actor = FoundActors[0];
    USkeletalMeshComponent* SkeletalMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();

    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found!"));
        return;
    }

    // Ensure the array has the correct size
    if (CurrentPositions.Num() < 5)
    {
        CurrentPositions.SetNumUninitialized(5);  // Adjust size accordingly
    }

    // Loop through the servos (servoHorn_06 to servoHorn_10)
    for (int i = 6; i <= 10; i++)
    {
        FString BoneNameStr = FString::Printf(TEXT("servoHorn_%02d"), i);
        FName BoneName(*BoneNameStr);

        int32 BoneIndex = SkeletalMesh->GetBoneIndex(BoneName);
        if (BoneIndex == INDEX_NONE)
        {
            UE_LOG(LogTemp, Error, TEXT("Bone %s not found!"), *BoneName.ToString());
            continue;
        }

        // Retrieve the current bone transform
        FTransform BoneTransform = SkeletalMesh->GetBoneTransform(BoneIndex);
        if (!BoneTransform.IsValid())
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid bone transform for bone: %s"), *BoneName.ToString());
            continue;
        }

        // Get the Y rotation directly
        float BoneRotationY = BoneTransform.GetRotation().Rotator().Pitch;

        // Track the lowest and highest Y rotation for the current servo
        if (!LowestRotation.Contains(i))
        {
            LowestRotation.Add(i, BoneRotationY);  // Initialize with the current rotation value
        }
        if (!HighestRotation.Contains(i))
        {
            HighestRotation.Add(i, BoneRotationY);  // Initialize with the current rotation value
        }

        // Update the lowest and highest rotation if necessary
        if (BoneRotationY < LowestRotation[i])
        {
            LowestRotation[i] = BoneRotationY;
        }
        if (BoneRotationY > HighestRotation[i])
        {
            HighestRotation[i] = BoneRotationY;
        }

        // Normalize the Y rotation to the servo range between 1500 and 2000
        float MappedServoPosition = 1500.0f + ((BoneRotationY - LowestRotation[i]) / (HighestRotation[i] - LowestRotation[i])) * (2000.0f - 1500.0f);

        // Ensure the mapped position is within the valid servo range (clamping to prevent out-of-bounds values)
        MappedServoPosition = FMath::Clamp(MappedServoPosition, 1500.0f, 2000.0f);

        // Store the current servo position
        CurrentPositions[i - 6] = MappedServoPosition;

        // Send the new servo position command
        FString SingleCommand = FString::Printf(TEXT("%d %.2f\n"), i - 6, MappedServoPosition);
        UE_LOG(LogTemp, Warning, TEXT("Sending servo data: %s"), *SingleCommand);
        SendServoData(SingleCommand);

        // Log the debug message for monitoring
        UE_LOG(LogTemp, Warning, TEXT("Servo: %d | Bone: %s | RotationY: %.2f | Mapped Servo Position: %.2f"),
            i - 6, *BoneName.ToString(), BoneRotationY, MappedServoPosition);
    }
}


bool AControlServoActor::OpenSerialPort()
{
    int RetryCount = 5;
    bool bPortOpened = false;

    while (RetryCount > 0 && !bPortOpened)
    {
        SerialPort = CreateFile(*PortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

        if (SerialPort != INVALID_HANDLE_VALUE)
        {
            DCB dcbSerialParams = { 0 };
            dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

            if (!GetCommState(SerialPort, &dcbSerialParams))
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to get serial port state"));
                CloseHandle(SerialPort);
                return false;
            }

            dcbSerialParams.BaudRate = CBR_115200;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;

            if (!SetCommState(SerialPort, &dcbSerialParams))
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to set serial port parameters"));
                CloseHandle(SerialPort);
                return false;
            }

            COMMTIMEOUTS timeouts = { 0 };
            timeouts.ReadIntervalTimeout = 50;
            timeouts.ReadTotalTimeoutConstant = 50;
            timeouts.ReadTotalTimeoutMultiplier = 10;
            timeouts.WriteTotalTimeoutConstant = 500;
            timeouts.WriteTotalTimeoutMultiplier = 10;

            if (!SetCommTimeouts(SerialPort, &timeouts))
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to set serial port timeouts"));
                CloseHandle(SerialPort);
                return false;
            }

            bPortOpened = true;
            UE_LOG(LogTemp, Log, TEXT("Successfully opened COM port %s."), *PortName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Retrying to open COM port %s..."), *PortName);
            --RetryCount;
        }
    }

    return bPortOpened;
}

void AControlServoActor::InitializeServoPositions()
{
    ServoPositions.Init(1500.0f, 7);
    ServoPositions[4] = 922.0f;
    ServoPositions[5] = 1300.0f;
    ServoPositions[6] = 1300.0f;

    CurrentPositions.Init(1500.0f, 7);
    bIsMoving = true;

    UE_LOG(LogTemp, Log, TEXT("Servo positions initialized."));
}

bool AControlServoActor::IsPortAvailable(const FString& InPortName)
{
    HANDLE TestHandle = CreateFile(*InPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (TestHandle == INVALID_HANDLE_VALUE)
    {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_ACCESS_DENIED)
        {
            UE_LOG(LogTemp, Warning, TEXT("Access to port %s is denied."), *InPortName);
        }
        else if (dwError == ERROR_FILE_NOT_FOUND)
        {
            UE_LOG(LogTemp, Warning, TEXT("Port %s not found."), *InPortName);
        }
        return false;
    }

    CloseHandle(TestHandle);
    return true;
}

void AControlServoActor::SendServoData(const FString& Command)
{
    if (SerialPort != INVALID_HANDLE_VALUE)
    {
        // Ensure the command string ends with a single newline
        FString CommandWithNewline = Command;

        // Check if the last character is already a newline
        if (!CommandWithNewline.EndsWith(TEXT("\r\n")))
        {
            // If it does not end with \r\n, append \r\n
            CommandWithNewline += TEXT("\r\n");
        }

        // Convert FString to char array
        FTCHARToUTF8 Convert(*CommandWithNewline);
        const char* CmdChars = Convert.Get();

        DWORD BytesWritten;
        WriteFile(SerialPort, CmdChars, strlen(CmdChars), &BytesWritten, NULL);
    }
}

