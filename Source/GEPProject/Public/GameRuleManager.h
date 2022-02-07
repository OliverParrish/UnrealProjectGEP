// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameRuleManager.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleSuccess, class AGameRuleManager*, DelegateInstigater);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleFailure, AGameRuleManager*, DelegateInstigater);

UCLASS(Abstract)
class GEPPROJECT_API AGameRuleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameRuleManager();

	UPROPERTY(BlueprintAssignable)
	FGameRuleSuccess OnGameRuleSuccess;

	UPROPERTY(BlueprintAssignable)
	FGameRuleFailure OnGameRuleFailure;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMatchEndingRule;

protected:

	void BroadcastGameRuleSuccess();
	void BroadcastGameRuleFailure();

};
