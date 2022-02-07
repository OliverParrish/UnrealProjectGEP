// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanWeapon.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AHitscanWeapon::AHitscanWeapon()
{
	Range = 2000.f;
	Damage = 25.f;
	MaxAmmo = 30;
}

void AHitscanWeapon::BeginPlay()
{
	CurAmmo = MaxAmmo;
	Super::BeginPlay();
}

bool AHitscanWeapon::Fire_Implementation(AActor* WeaponOwner, APawn* FireInstigator)
{
	if(CurAmmo <= 0)
	{
		return false;
	}
	
	UWorld* const world = GetWorld();
	if (world != nullptr)
	{
		
		FHitResult hit(ForceInit);
		UArrowComponent* muzzle = GetGunMuzzle();
		FVector start = UGameplayStatics::GetPlayerController(world, 0)->PlayerCameraManager->GetCameraLocation();
		FVector forward = UGameplayStatics::GetPlayerController(world, 0)->PlayerCameraManager->GetActorForwardVector();
		FVector end = (forward * Range) + start;
       
		const FName traceTag("TraceTag");
		world->DebugDrawTraceTag = traceTag; //Draws arrow at hit point
		FCollisionQueryParams collisionParams;
		collisionParams.TraceTag = traceTag;
		
		if (world->LineTraceSingleByChannel(hit, start,end, ECC_Visibility, collisionParams))
		{
			if(hit.GetActor() != nullptr)
			{
				
				UGameplayStatics::ApplyDamage(hit.GetActor(), Damage, FireInstigator->GetInstigatorController(),
				WeaponOwner, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
			}
		}
	}
	CurAmmo--;
	return true;
}

bool AHitscanWeapon::Reload_Implementation(AActor* WeaponOwner, APawn* ReloadInstigator)
{
	if(CurAmmo >= MaxAmmo)
	{
		return false;
	}

	CurAmmo = MaxAmmo;
	return true;
}

