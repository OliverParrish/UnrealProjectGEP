// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRuleManager.h"
#include "GEPProject/EnemyAI.h"
#include "GEPProject/Initable.h"
#include "GameRuleManager_Enemies.generated.h"


UCLASS(Abstract)
class GEPPROJECT_API AGameRuleManager_Enemies : public AGameRuleManager, public IInitable
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EnemySpawnPointClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyAI> EnemyToSpawn;

	virtual void Init_Implementation() override;

protected:

	int m_AmountRemaining;
	
	TArray<AActor*> SpawnPoints;
	
	TArray<AEnemyAI*> Enemies;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EnemyDead(AEnemyAI* delegateInstigator);
};
