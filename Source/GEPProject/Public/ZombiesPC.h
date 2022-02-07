// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GEPProject/Initable.h"
#include "GEPProject/MatchStateHandler.h"
#include "ZombiesPC.generated.h"

class AZombiesPChar;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthBarPercentUpdate, float, healthUpdate);

UCLASS()
class GEPPROJECT_API AZombiesPC : public APlayerController, public IInitable, public IMatchStateHandler
{
	GENERATED_BODY()
	
public:

	virtual void SetupInputComponent() override;
	virtual void Init_Implementation() override;
	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchFinished_Implementation() override;

	FHealthBarPercentUpdate OnHealthBarUpdate;

	UFUNCTION()
	void HealthBarUpdate(float update);

	UFUNCTION(BlueprintNativeEvent)
	void OnCharDied(AZombiesPChar* Char);
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> pawnToSpawn;

private:

	virtual void OnPossess(APawn* InPawn) override;
	
	void JumpPressed(); void JumpReleased();
	void FirePressed(); void FireReleased();
	void SprintPressed(); void SprintReleased();
	void ReloadPressed();

	void MoveForward(float value);
	void MoveRight(float value);

	void LookUp(float value);
	void Turn(float value);

	void LookUpAtRate(float value);
	void TurnAtRate(float value);
};



