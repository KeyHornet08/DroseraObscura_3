#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"  
#include <Windows.h>  
#include "StepperControl.generated.h"

UCLASS()
class TESTTWO_API AStepperControl : public AActor  
{
    GENERATED_BODY()

public:
    
    AStepperControl();


    virtual ~AStepperControl();

 
    virtual void BeginPlay() override;

 
    virtual void Tick(float DeltaTime) override;


private:
    HANDLE SerialHandle;
    FString PortName;

    float GetServoHornRotationY();
    float GetServoHornRotationY(FName BoneName);

    bool OpenSerialPort();
    void CloseSerialPort();
    void SendSerialData(const FString& Data);
    void SendGCode(const FString& GCode);

    float XValue;
    float ZValue;

    float LastXValue;
    float LastZValue;

    AActor* FindActorByName(FName ActorName);
};
