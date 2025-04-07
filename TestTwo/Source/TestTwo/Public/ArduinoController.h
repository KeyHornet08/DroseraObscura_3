#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "ArduinoController.generated.h" 

UCLASS()
class TESTTWO_API AArduinoController : public AActor
{
    GENERATED_BODY()

public:
   
    AArduinoController();

protected:
   
    virtual void BeginPlay() override;

public:
    
    virtual void Tick(float DeltaTime) override;

private:
    FString ArduinoIP;  

    
    void SendHttpRequest(FString Command);

public:
    
    UFUNCTION(BlueprintCallable, Category = "Arduino")
    void TurnPumpOn();

    UFUNCTION(BlueprintCallable, Category = "Arduino")
    void TurnPumpOff();
};
