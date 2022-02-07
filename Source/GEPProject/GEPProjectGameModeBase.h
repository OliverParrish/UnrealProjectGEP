// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GEPProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GEPPROJECT_API AGEPProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	
	TArray<AActor*> Spawners;

	UFUNCTION()
    void EnemySpawned();
	
	UFUNCTION()
	void EnemyDied();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ClassToFind;

	int EnemyCount;
};
