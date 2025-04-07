#include "ArduinoController.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

AArduinoController::AArduinoController()
{
    PrimaryActorTick.bCanEverTick = true;
    ArduinoIP = TEXT("10.0.1.3");
}


void AArduinoController::BeginPlay()
{
    Super::BeginPlay();

    if (!FHttpModule::Get().IsHttpEnabled())
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP module is not enabled!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("HTTP module is ready."));

        TurnPumpOn();

    }
}


void AArduinoController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AArduinoController::TurnPumpOn()
{
    SendHttpRequest("1");
}


void AArduinoController::TurnPumpOff()
{
    SendHttpRequest("0");
}

void AArduinoController::SendHttpRequest(FString Command)
{
    if (ArduinoIP.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Arduino IP not set!"));
        return;
    }

    FString Url = FString::Printf(TEXT("http://%s/%s"), *ArduinoIP, *Command);

    UE_LOG(LogTemp, Log, TEXT("Sending request to URL: %s"), *Url);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

    Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
        {
            if (bSuccess && Response.IsValid())
            {
                UE_LOG(LogTemp, Log, TEXT("Arduino Response: %s"), *Response->GetContentAsString());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to communicate with Arduino over WiFi"));
            }
        });

    Request->SetURL(Url);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();
}
