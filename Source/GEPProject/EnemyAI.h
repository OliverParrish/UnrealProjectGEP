// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GetEnemyAI.h"
#include "Chaos/AABBTree.h"
#include "Chaos/AABBTree.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDied, AEnemyAI* , delegateInstigator);

UCLASS(Abstract)
class GEPPROJECT_API AEnemyAI : public ACharacter, public IGetEnemyAI
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	
public:
	// Sets default values for this character's properties
	AEnemyAI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyDied OnEnemyDeath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float m_AttackCooldown;
	
	UFUNCTION(BlueprintCallable)
	void DealDamage(AActor* ActorToDamage);

	void Init();
protected:

	UPROPERTY(EditAnywhere)
	float Damage;

	UFUNCTION()
	void Death(AController* DamageInstigator);


public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual AEnemyAI* GetEnemyAI_Implementation() override { return this; }
};
