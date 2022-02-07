// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GetPlayerCharacter.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "GEPProject/Initable.h"
#include "ZombiesPChar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthBarUpdate, float, healthUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeath, AZombiesPChar*, deligateInstigator);

UCLASS()
class GEPPROJECT_API AZombiesPChar : public ACharacter, public IInitable, public IInputable, public IGetPlayerCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CamBoomArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* m_ChildActor_Gun;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* WeaponSocketComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	
public:
	// Sets default values for this character's properties
	AZombiesPChar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;
	
	virtual void Init_Implementation() override;

	UPROPERTY(BlueprintAssignable)
	FHealthBarUpdate OnHealthUpdate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeath OnPlayerDeath;

#pragma region input_interface_functions

	virtual void JumpPressed_Implementation() override;
	virtual void JumpReleased_Implementation() override;
	virtual void FirePressed_Implementation() override;
	virtual void FireReleased_Implementation() override;
	virtual void SprintPressed_Implementation() override;
	virtual void SprintReleased_Implementation() override;
	virtual void ReloadPressed_Implementation() override;

	virtual void MoveForward_Implementation(float value) override;
	virtual void MoveRight_Implementation(float value) override;
	virtual void LookUp_Implementation(float value) override;
	virtual void Turn_Implementation(float value) override;

	virtual void LookUpAtRate_Implementation(float value) override;
	virtual void TurnAtRate_Implementation(float value) override;
	
#pragma endregion

	virtual AZombiesPChar* ReturnCharacter_Implementation() override;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSprinting;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Death(AController* DamageInstigator);

	UFUNCTION()
	void HealthUpdate(float healthUpdate);
};

