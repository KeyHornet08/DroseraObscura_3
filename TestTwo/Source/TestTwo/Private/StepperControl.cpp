#include "StepperControl.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/MinWindows.h"
#include <commdlg.h>
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "HAL/PlatformProcess.h"

AStepperControl::AStepperControl()
{
    PrimaryActorTick.bCanEverTick = true;
    SerialHandle = INVALID_HANDLE_VALUE;
    PortName = TEXT("COM10");

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
        UE_LOG(LogTemp, Log, TEXT("Serial port opened successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to open serial port! Check port name, cable, drivers, or if another program is using the port."));
    }

    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        UE_LOG(LogTemp, Warning, TEXT("Actor in scene: %s"), *It->GetName());
    }
}

void AStepperControl::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float YRotation1 = GetServoHornRotationY(TEXT("servoHorn_00"));
    float YRotation2 = GetServoHornRotationY(TEXT("servoHorn_03"));

    XValue = FMath::GetMappedRangeValueClamped(FVector2D(-8, 6), FVector2D(-15, 15), YRotation1);
    ZValue = FMath::GetMappedRangeValueClamped(FVector2D(-8, 6), FVector2D(-15, 15), YRotation2);

    UE_LOG(LogTemp, Log, TEXT("servoHorn_00 Y-Rotation: %.2f, servoHorn_03 Y-Rotation: %.2f"), YRotation1, YRotation2);

    FString GCodeCommand = FString::Printf(TEXT("G1 X%.2f Z%.2f F500"), XValue, ZValue);
    SendGCode(GCodeCommand);
}

float AStepperControl::GetServoHornRotationY(FName BoneName)
{
    AActor* TargetActor = nullptr;

    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (It->GetName().Contains(TEXT("ObsucreaOneTest")))
        {
            TargetActor = *It;
            break;
        }
    }

    if (!TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find actor with name containing 'ObsucreaOneTest'"));
        return 0.0f;
    }

    USkeletalMeshComponent* SkeletalMesh = TargetActor->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkeletalMesh)
    {
        UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found!"));
        return 0.0f;
    }

    int32 BoneIndex = SkeletalMesh->GetBoneIndex(BoneName);
    if (BoneIndex == INDEX_NONE)
    {
        UE_LOG(LogTemp, Error, TEXT("Bone '%s' not found in skeletal mesh!"), *BoneName.ToString());
        return 0.0f;
    }

    FTransform BoneTransform = SkeletalMesh->GetBoneTransform(BoneIndex);
    float BoneRotationY = BoneTransform.GetRotation().Rotator().Pitch;

    return BoneRotationY;
}

void AStepperControl::SendGCode(const FString& GCode)
{
    if (SerialHandle != INVALID_HANDLE_VALUE)
    {
        FString CommandWithLineEnd = GCode + TEXT("\r\n");
        const char* CommandStr = TCHAR_TO_UTF8(*CommandWithLineEnd);
        DWORD bytesWritten;

        bool success = WriteFile(SerialHandle, CommandStr, strlen(CommandStr), &bytesWritten, nullptr);

        if (success)
        {
            UE_LOG(LogTemp, Log, TEXT("Sent GCode: %s"), *GCode);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to send GCode to Arduino!"));
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
        UE_LOG(LogTemp, Error, TEXT("CreateFile failed for port %s"), *PortName);
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(SerialHandle, &dcbSerialParams))
    {
        UE_LOG(LogTemp, Error, TEXT("GetCommState failed"));
        CloseHandle(SerialHandle);
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(SerialHandle, &dcbSerialParams))
    {
        UE_LOG(LogTemp, Error, TEXT("SetCommState failed"));
        CloseHandle(SerialHandle);
        return false;
    }

    // Allow board time to reset
    FPlatformProcess::Sleep(2.0f);
    UE_LOG(LogTemp, Log, TEXT("Serial port opened and ready."));

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
