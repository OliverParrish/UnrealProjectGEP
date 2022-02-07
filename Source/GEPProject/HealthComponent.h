// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeath, AController*, DamageInstigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthUpdate, float , HealthPercent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEPPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FDeath OnDeath;

	FHealthUpdate OnHealthUpdate;

	virtual void Init();

protected:
	// Called when the game starts

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartingHealth;

	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UFUNCTION(BlueprintCallable)
    virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
    	class AController* InstigatedBy, AActor* DamageCauser);

		
};
