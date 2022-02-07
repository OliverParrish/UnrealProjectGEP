// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GetEnemySpawner.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemySpawned);

UCLASS()
class GEPPROJECT_API AEnemySpawner : public AActor, public IGetEnemySpawner
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoundingBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EnemyToSpawn;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AEnemySpawner* GetEnemySpawner();
	virtual AEnemySpawner* GetEnemySpawner_Implementation()override;

	FOnEnemyDeath OnEnemyDeath;
	FOnEnemySpawned OnEnemySpawned;
	
	void Init();
	
protected:

	void SpawnEnemy();

	UFUNCTION()
	void EnemyDied();


};
