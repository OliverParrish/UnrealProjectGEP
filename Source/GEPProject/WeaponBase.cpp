// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Engine/Engine.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	RootComponent = m_Root;

	m_GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	m_GunMesh->SetupAttachment(m_Root);

	m_GunMuzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("GunMuzzle"));
	m_GunMuzzle->SetupAttachment(m_GunMesh);
}

bool AWeaponBase::Fire_Implementation(AActor* WeaponOwner, APawn* FireInstigator)
{
	return true;
}

bool AWeaponBase::Reload_Implementation(AActor* WeaponOwner, APawn* ReloadInstigator)
{
	return true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


