// Fill out your copyright notice in the Description page of Project Settings.


#include "SendRequest.h"


USendRequest* USendRequest::SendRequest(UObject* worldContextObject, FString method, FString url)
{
    auto Platform = NewObject<USendRequest>();
    Platform->AddToRoot();
    Platform->Http = &FHttpModule::Get();
    Platform->Method = method;
    Platform->Url = url;

    return Platform;
}

void USendRequest::Activate()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &USendRequest::OnResponseReceived);
    Request->SetURL(this->Url);
    Request->SetVerb(this->Method);
    Request->SetHeader("Context-Type", TEXT("application/json"));
    Request->ProcessRequest();   
}

void USendRequest::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    TSharedPtr<FJsonObject> JsonObject;
    FString ResponseString = Response->GetContentAsString();

    Callback.Broadcast(ResponseString);
    SetReadyToDestroy();

}
