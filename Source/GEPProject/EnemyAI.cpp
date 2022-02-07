// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAI.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AEnemyAI::Init()
{
	HealthComponent->Init();
	HealthComponent->OnDeath.AddDynamic(this, &AEnemyAI::Death);
}

void AEnemyAI::Death(AController* DamageInstigator)
{
	//Get enemy to ragdoll on death
	GetCapsuleComponent()->SetCollisionProfileName("IgnoreOnlyPawn", false);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetMesh()->SetCollisionProfileName("Ragdoll", false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	GetMesh()->SetSimulatePhysics(true);
	GetController()->UnPossess();
	
	OnEnemyDeath.Broadcast(this);
}

void AEnemyAI::DealDamage(AActor* ActorToDamage)
{
	UGameplayStatics::ApplyDamage(ActorToDamage, Damage,
		GetInstigatorController(),this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


