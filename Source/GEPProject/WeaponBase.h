// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fireable.h"
#include "Reloadable.h"
#include "Chaos/AABBTree.h"

#include "WeaponBase.generated.h"

UCLASS()
class GEPPROJECT_API AWeaponBase : public AActor, public IFireable, public IReloadable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
	
	virtual bool Fire_Implementation(AActor* WeaponOwner, APawn* FireInstigator = nullptr) override;
	virtual bool Reload_Implementation(AActor* WeaponOwner, APawn* ReloadInstigator) override;

	FORCEINLINE class UArrowComponent* GetGunMuzzle() const {return m_GunMuzzle; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* m_Root;

	UPROPERTY(VisibleDefaultsOnly)
	class USkeletalMeshComponent* m_GunMesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UArrowComponent* m_GunMuzzle;

};
