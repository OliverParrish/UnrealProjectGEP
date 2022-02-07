// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


#include "EnemyAI.h"
#include "GetEnemyAI.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundingBox"));
}

AEnemySpawner* AEnemySpawner::GetEnemySpawner_Implementation()
{
	return this;
	
}

// Called when the game starts or when spawned
void AEnemySpawner::Init()
{
	SpawnEnemy();
}

void AEnemySpawner::SpawnEnemy()
{
	UWorld* const world =  GetWorld();
	
	if (world != nullptr && EnemyToSpawn)
	{
		FVector origin = BoundingBox->GetComponentLocation();
		FVector extents = BoundingBox->GetScaledBoxExtent();

		FVector spawnPosition = UKismetMathLibrary::RandomPointInBoundingBox(origin, extents);
		FRotator spawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* tempActor = world->SpawnActor<AActor>(EnemyToSpawn, spawnPosition, spawnRotation, actorSpawnParams);

		if (UKismetSystemLibrary::DoesImplementInterface(tempActor, UGetEnemyAI::StaticClass()))
		{
			AEnemyAI* TempEnemyAI = IGetEnemyAI::Execute_GetEnemyAI(tempActor);
			TempEnemyAI->Init();
		}
		
		OnEnemySpawned.Broadcast();
	}
	
}

void AEnemySpawner::EnemyDied()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy Died")));
	OnEnemyDeath.Broadcast();
}
