// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Chaos/AABBTree.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	AEnemyAIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RangeKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName AttackCooldownKeyName;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAIPerceptionComponent* AIPerceptionComponent;
};
