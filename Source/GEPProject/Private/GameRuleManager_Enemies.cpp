// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRuleManager_Enemies.h"
#include "Kismet/GameplayStatics.h"

void AGameRuleManager_Enemies::Init_Implementation()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemySpawnPointClass, SpawnPoints);
	
	FActorSpawnParameters actorSpawnParams;
	actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	UWorld* const world =  GetWorld();
	
	if (world != nullptr && EnemyToSpawn)
	{

		FVector spawnPosition;
		FRotator spawnRotation;
		AEnemyAI* tempActor;
		
		for (AActor* spawnPoint : SpawnPoints)
		{
			
			spawnPosition = spawnPoint->GetActorLocation();
			spawnRotation = spawnPoint->GetActorRotation();

			tempActor = world->SpawnActor<AEnemyAI>(EnemyToSpawn, spawnPosition, spawnRotation, actorSpawnParams);
			Enemies.Add(tempActor);

			tempActor->OnEnemyDeath.AddDynamic(this, &AGameRuleManager_Enemies::EnemyDead);
			tempActor->Init();
		}
		
		m_AmountRemaining = Enemies.Num();
	}
}

void AGameRuleManager_Enemies::EnemyDead_Implementation(AEnemyAI* delegateInstigator)
{
	m_AmountRemaining --;
	if(m_AmountRemaining == 0)
	{
		BroadcastGameRuleSuccess();
	}
}
