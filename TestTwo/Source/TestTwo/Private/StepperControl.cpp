#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "StepperControl.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

AStepperControl::AStepperControl()
{
    PrimaryActorTick.bCanEverTick = true;

    PortName = TEXT("COM10");
    XValue = ZValue = LastXValue = LastZValue = 0.0f;
    SerialHandle = nullptr;
}

AStepperControl::~AStepperControl()
{
    CloseSerialPort();
}

void AStepperControl::BeginPlay()
{
    Super::BeginPlay();

    if (!OpenSerialPort())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to open serial port."));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Serial port opened successfully."));
    }
}

void AStepperControl::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float BoneY = GetServoHornRotationY(FName("servoHorn_00"));

    ZValue = FMath::Clamp(BoneY * 2.0f, -15.0f, 15.0f);
    XValue = FMath::Clamp(BoneY * 1.0f, 0.0f, 15.0f);

    if (!FMath::IsNearlyEqual(XValue, LastXValue) || !FMath::IsNearlyEqual(ZValue, LastZValue))
    {
        FString GCode = FString::Printf(TEXT("G1 X%.2f Z%.2f F500"), XValue, ZValue);
        SendGCode(GCode);

        UE_LOG(LogTemp, Display, TEXT("Updated X: %.2f -> %.2f, Z: %.2f -> %.2f"), LastXValue, XValue, LastZValue, ZValue);

        LastXValue = XValue;
        LastZValue = ZValue;
    }
}

float AStepperControl::GetServoHornRotationY(FName BoneName)
{
    AActor* FoundActor = FindActorByName(FName("ObsucreaOneTest"));
    if (!FoundActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not find actor: ObsucreaOneTest"));
        return 0.0f;
    }

    USkeletalMeshComponent* SkelMesh = FoundActor->FindComponentByClass<USkeletalMeshComponent>();
    if (!SkelMesh || !SkelMesh->DoesSocketExist(BoneName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Bone or mesh not found: %s"), *BoneName.ToString());
        return 0.0f;
    }

    FRotator BoneRot = SkelMesh->GetBoneQuaternion(BoneName).Rotator();
    return BoneRot.Yaw;
}

bool AStepperControl::OpenSerialPort()
{
    FString FullPort = FString("\\\\.\\") + PortName;
    SerialHandle = CreateFileW(*FullPort, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    if (SerialHandle == INVALID_HANDLE_VALUE)
    {
        SerialHandle = nullptr;
        return false;
    }

    DCB SerialParams = { 0 };
    SerialParams.DCBlength = sizeof(SerialParams);

    if (!GetCommState(SerialHandle, &SerialParams))
    {
        CloseHandle(SerialHandle);
        SerialHandle = nullptr;
        return false;
    }

    SerialParams.BaudRate = CBR_115200;
    SerialParams.ByteSize = 8;
    SerialParams.StopBits = ONESTOPBIT;
    SerialParams.Parity = NOPARITY;

    if (!SetCommState(SerialHandle, &SerialParams))
    {
        CloseHandle(SerialHandle);
        SerialHandle = nullptr;
        return false;
    }

    COMMTIMEOUTS Timeouts = { 0 };
    Timeouts.ReadIntervalTimeout = 50;
    Timeouts.ReadTotalTimeoutConstant = 50;
    Timeouts.ReadTotalTimeoutMultiplier = 10;
    Timeouts.WriteTotalTimeoutConstant = 50;
    Timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(SerialHandle, &Timeouts))
    {
        CloseHandle(SerialHandle);
        SerialHandle = nullptr;
        return false;
    }

    return true;
}

void AStepperControl::CloseSerialPort()
{
    if (SerialHandle)
    {
        CloseHandle(SerialHandle);
        SerialHandle = nullptr;
    }
}

void AStepperControl::SendSerialData(const FString& Data)
{
    if (!SerialHandle || SerialHandle == INVALID_HANDLE_VALUE) return;

    FTCHARToUTF8 UTF8(*Data);
    DWORD BytesWritten;
    WriteFile(SerialHandle, UTF8.Get(), UTF8.Length(), &BytesWritten, nullptr);
}

void AStepperControl::SendGCode(const FString& GCode)
{
    FString Command = GCode + TEXT("\n");
    SendSerialData(Command);
    UE_LOG(LogTemp, Display, TEXT("Sent G-code: %s"), *GCode);
}

AActor* AStepperControl::FindActorByName(FName ActorName)
{
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (It->GetFName() == ActorName)
        {
            return *It;
        }
    }
    return nullptr;
}
