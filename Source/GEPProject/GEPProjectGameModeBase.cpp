// Copyright Epic Games, Inc. All Rights Reserved.


#include "GEPProjectGameModeBase.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

void AGEPProjectGameModeBase::BeginPlay()
{
	EnemyCount = 0;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, Spawners);

	for (AActor* Element : Spawners)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Element, UGetEnemySpawner::StaticClass()))
		{
			AEnemySpawner* TempSpawner = IGetEnemySpawner::Execute_GetEnemySpawner(Element);
			TempSpawner->OnEnemySpawned.AddDynamic(this, &AGEPProjectGameModeBase::EnemySpawned);
			TempSpawner->OnEnemyDeath.AddDynamic(this, &AGEPProjectGameModeBase::EnemyDied);
			TempSpawner->Init();
		}
	}
}

void AGEPProjectGameModeBase::EnemySpawned()
{
	EnemyCount++;
}

void AGEPProjectGameModeBase::EnemyDied()
{
	EnemyCount--;

	if(EnemyCount <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Game Over, You Win!")));
	}
	
}
