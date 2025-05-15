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

    XValue = 0.0f;
    ZValue = 0.0f;
    LastXValue = NAN;
    LastZValue = NAN;
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


    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        UE_LOG(LogTemp, Warning, TEXT("Actor in scene: %s"), *It->GetName());
    }
}

void AStepperControl::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeSinceLastSend += DeltaTime;
    if (TimeSinceLastSend < SendInterval)
        return;

    TimeSinceLastSend = 0.0f;

    float YRotation1 = GetServoHornRotationY(TEXT("servoHorn_00"));
    float YRotation2 = GetServoHornRotationY(TEXT("servoHorn_03"));

    XValue = FMath::GetMappedRangeValueClamped(FVector2D(-8, 6), FVector2D(-15, 15), YRotation1);
    ZValue = FMath::GetMappedRangeValueClamped(FVector2D(-8, 6), FVector2D(-15, 15), YRotation2);

    UE_LOG(LogTemp, Log, TEXT("servoHorn_00 Y-Rotation: %.2f, servoHorn_03 Y-Rotation: %.2f"), YRotation1, YRotation2);
    UE_LOG(LogTemp, Log, TEXT("Sending Final GCode: G1 X%.2f Z%.2f F500"), XValue, ZValue);

    FString GCodeCommand = FString::Printf(TEXT("G1 X%.2f Z%.2f F500"), XValue, ZValue);
    SendGCode(GCodeCommand);
}


float AStepperControl::GetServoHornRotationY(FName BoneName)
{
    AActor* TargetActor = nullptr;

    TArray<AActor*> TaggedActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("ObsucreaOneTest"), TaggedActors);

    if (TaggedActors.Num() > 0)
    {
        TargetActor = TaggedActors[0];

    }
    else
    {
        for (TActorIterator<AActor> It(GetWorld()); It; ++It)
        {
            if (It->GetName().Contains(TEXT("ObsucreaOneTest")))
            {
                TargetActor = *It;
                UE_LOG(LogTemp, Log, TEXT("Found actor by name: %s"), *TargetActor->GetName());
                break;
            }
        }
    }

    if (!TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find actor matching 'ObsucreaOneTest'"));
        return 0.0f;
    }

    USkeletalMeshComponent* SkeletalMesh = TargetActor->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found on %s"), *TargetActor->GetName());
        return 0.0f;
    }

    int32 BoneIndex = SkeletalMesh->GetBoneIndex(BoneName);
    if (BoneIndex == INDEX_NONE)
    {
        UE_LOG(LogTemp, Error, TEXT("Bone '%s' not found"), *BoneName.ToString());
        return 0.0f;
    }

    FTransform BoneTransform = SkeletalMesh->GetBoneTransform(BoneIndex);
    return BoneTransform.GetRotation().Rotator().Pitch;

    
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
        UE_LOG(LogTemp, Log, TEXT("Serial port closed."));
    }
}
