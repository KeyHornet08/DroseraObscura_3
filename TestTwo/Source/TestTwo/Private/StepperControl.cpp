#include "StepperControl.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"
#include <commdlg.h>
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

AStepperControl::AStepperControl()
{
    PrimaryActorTick.bCanEverTick = true;
    SerialHandle = INVALID_HANDLE_VALUE;
    PortName = TEXT("COM6");

    // Initialize X and Z values to 0
    XValue = 0.0f;
    ZValue = 0.0f;
}

AStepperControl::~AStepperControl()
{
    if (SerialHandle != INVALID_HANDLE_VALUE)
    {
        CloseSerialPort();
    }
}

void AStepperControl::BeginPlay()
{
    Super::BeginPlay();

    if (OpenSerialPort())
    {
        UE_LOG(LogTemp, Log, TEXT("Serial port opened successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to open serial port"));
    }
}

void AStepperControl::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Get the Y rotation of servoHorn_00 and servoHorn_03
    float YRotation1 = GetServoHornRotationY(TEXT("servoHorn_00"));
    float YRotation2 = GetServoHornRotationY(TEXT("servoHorn_03"));

    // Map Y rotation of servoHorn_00 (-8 to 6) to X (-15 to 15) – flipped
    XValue = FMath::GetMappedRangeValueClamped(FVector2D(-8, 6), FVector2D(-15, 15), YRotation1);

    // Map Y rotation of servoHorn_03 (-8 to 6) to Z (-15 to 15) – flipped
    ZValue = FMath::GetMappedRangeValueClamped(FVector2D(-8, 6), FVector2D(-15, 15), YRotation2);

    // Log the updated values for debugging
    UE_LOG(LogTemp, Log, TEXT("servoHorn_00 Y-Rotation: %.2f, servoHorn_03 Y-Rotation: %.2f"), YRotation1, YRotation2);
    UE_LOG(LogTemp, Log, TEXT("Sending Final GCode: G1 X%.2f Z%.2f F500"), XValue, ZValue);

    // Send the new GCode with the updated X and Z values
    FString GCodeCommand = FString::Printf(TEXT("G1 X%.2f Z%.2f F500"), XValue, ZValue);
    SendGCode(GCodeCommand);
}

float AStepperControl::GetServoHornRotationY(FName BoneName)
{
    // Get actors with the specific tag in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ObsucreaOneTest_1"), FoundActors);

    if (FoundActors.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Actor with tag 'ObsucreaOneTest_1' not found!"));
        return 0.0f;
    }

    // Check if the found actor is of type AActor
    AActor* Actor = Cast<AActor>(FoundActors[0]);

    if (!Actor)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast actor!"));
        return 0.0f;  // Return default value if cast fails
    }

    // Retrieve SkeletalMeshComponent from the actor
    USkeletalMeshComponent* SkeletalMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();

    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found!"));
        return 0.0f;
    }

    // Get the bone index for the given bone name
    int32 BoneIndex = SkeletalMesh->GetBoneIndex(BoneName);

    if (BoneIndex == INDEX_NONE)
    {
        UE_LOG(LogTemp, Error, TEXT("Bone '%s' not found in skeletal mesh!"), *BoneName.ToString());
        return 0.0f;  // Return default value if bone is not found
    }

    // Get the bone transform and extract the Y rotation (pitch)
    FTransform BoneTransform = SkeletalMesh->GetBoneTransform(BoneIndex);
    float BoneRotationY = BoneTransform.GetRotation().Rotator().Pitch;

    // Return the Y rotation
    return BoneRotationY;
}


void AStepperControl::SendGCode(const FString& GCode)
{
    if (SerialHandle != INVALID_HANDLE_VALUE)
    {
        FString CompleteGCode = GCode;

        if (!CompleteGCode.Contains(TEXT("Z")))
        {
            UE_LOG(LogTemp, Warning, TEXT("WARNING: Z Value Missing! Appending default Z0."));
            CompleteGCode += TEXT(" Z0");
        }

        if (!CompleteGCode.Contains(TEXT("F")))
        {
            CompleteGCode += TEXT(" F500");
        }

        FString CommandWithLineEnd = CompleteGCode + TEXT("\r\n");

        UE_LOG(LogTemp, Log, TEXT("Sending Final GCode: %s"), *CommandWithLineEnd);

        const char* CommandStr = TCHAR_TO_UTF8(*CommandWithLineEnd);
        DWORD bytesWritten;
        bool success = WriteFile(SerialHandle, CommandStr, strlen(CommandStr), &bytesWritten, nullptr);

        if (success)
        {
            UE_LOG(LogTemp, Log, TEXT("Sent GCode: %s"), ANSI_TO_TCHAR(CommandStr));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to send GCode!"));
        }
    }
}

bool AStepperControl::OpenSerialPort()
{
    SerialHandle = CreateFile(*PortName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr);

    if (SerialHandle == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(SerialHandle, &dcbSerialParams))
    {
        CloseHandle(SerialHandle);
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(SerialHandle, &dcbSerialParams))
    {
        CloseHandle(SerialHandle);
        return false;
    }

    return true;
}

void AStepperControl::CloseSerialPort()
{
    if (SerialHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(SerialHandle);
        SerialHandle = INVALID_HANDLE_VALUE;
    }
}
