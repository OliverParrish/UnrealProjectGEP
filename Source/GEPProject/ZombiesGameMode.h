// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Chaos/AABBTree.h"
#include "GameFramework/GameMode.h"
#include "ZombiesGameMode.generated.h"

class AGameRuleManager;

UCLASS()
class GEPPROJECT_API AZombiesGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	
protected:

	bool isWin;
	
	int m_GameRulesLeft;

	float healthPercent;
	
	TArray<AActor*> m_PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AController*> m_PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchManagement")
	TSubclassOf<APawn> m_PlayingPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MatchManagement")
	TMap<AGameRuleManager*, bool> m_GameRuleManagers;

	FTimerHandle MatchStartTimer;

    UFUNCTION()
	void HandleGameRuleSuccess(AGameRuleManager* delegateInstigator);

	UFUNCTION()
	void HandleGameRuleFailure(AGameRuleManager* delegateInstigator);
	
	virtual void BeginPlay() override;
	
	FORCEINLINE bool ReadyToStartMatch_Implementation() override{return false;}
	FORCEINLINE bool ReadyToEndMatch_Implementation() override {return false;}

	virtual void OnMatchStateSet() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	
};

