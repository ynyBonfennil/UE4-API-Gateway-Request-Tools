// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "SendRequest.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResponseReceivedCallback, FString, responseString);
/**
 * 
 */
UCLASS()
class RESTAPITOOLS_API USendRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	FHttpModule* Http;
	FString Method;
	FString Url;

	UPROPERTY(BlueprintAssignable)
		FOnResponseReceivedCallback Callback;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", Category = "REST API Tools"))
		static USendRequest* SendRequest(UObject* worldContextObject, FString method, FString url);


private:
	virtual void Activate() override;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
