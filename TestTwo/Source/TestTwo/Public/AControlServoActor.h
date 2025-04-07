#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Windows.h>
#include "AControlServoActor.generated.h"

UCLASS()
class TESTTWO_API AControlServoActor : public AActor
{
    GENERATED_BODY()

public:
    AControlServoActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Serial communication
    bool OpenSerialPort();
    void CloseSerialPort();
    void SendServoData(const FString& Command);

    // Servo control
    float GetServoHornRotationY(FName BoneName); // Ensure this exists to match .cpp file

private:
    void AttachToSkeletalMesh(USkeletalMeshComponent* SkeletalMesh);
    void UpdateServoPositionsFromAnimation();
    void InitializeServoPositions();
    bool IsPortAvailable(const FString& InPortName);
    void SendServoData(int ServoIndex, float Position);


    // Serial communication members
    HANDLE SerialPort;
    HANDLE SerialHandle;
    FString PortName = TEXT("COM3");


    // Servo position storage
    TArray<float> ServoPositions;
    TArray<float> CurrentPositions;
    bool bIsMoving;

    // Threading
    FRunnableThread* Thread;
    TMap<int32, float> LowestRotation;
    TMap<int32, float> HighestRotation;
};
