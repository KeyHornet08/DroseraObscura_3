#pragma once

#include <Windows.h>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StepperControl.generated.h"

UCLASS()
class TESTTWO_API AStepperControl : public AActor
{
    GENERATED_BODY()

public:
    AStepperControl();
    virtual ~AStepperControl();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    void SendSerialData(const FString& Data);
    void SendGCode(const FString& GCode);
    bool OpenSerialPort();
    void CloseSerialPort();
    float GetServoHornRotationY(FName BoneName);
    AActor* FindActorByTag(FName ActorTag);

private:
    HANDLE SerialHandle;
    FString PortName;

    float XValue;
    float ZValue;
    float LastXValue;
    float LastZValue;
};
