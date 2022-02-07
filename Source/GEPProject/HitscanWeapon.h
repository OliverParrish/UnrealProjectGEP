// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Chaos/AABBTree.h"

#include "HitscanWeapon.generated.h"


UCLASS(Abstract)
class GEPPROJECT_API AHitscanWeapon : public AWeaponBase
{
	GENERATED_BODY()
	

public:

	AHitscanWeapon();
	
	virtual bool Fire_Implementation(AActor* WeaponOwner, APawn* FireInstigator = nullptr) override;
	virtual bool Reload_Implementation(AActor* WeaponOwner, APawn* ReloadInstigator) override;


protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmo;
	int CurAmmo;
};
