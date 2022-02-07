// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	StartingHealth = 100;
}

// Called when the game starts
void UHealthComponent::Init()
{
	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	
	Health = StartingHealth;
	OnHealthUpdate.Broadcast(1.f);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Health <= 0)
	{
		return;
	}
	
	Health -= Damage;
	
	OnHealthUpdate.Broadcast(Health / StartingHealth);
	
	if(Health <= 0)
	{
		OnDeath.Broadcast(InstigatedBy);
	}
}

