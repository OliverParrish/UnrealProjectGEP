// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiesGameMode.h"
#include "EngineUtils.h"
#include "GameRuleManager.h"
#include "Initable.h"
#include "MatchStateHandler.h"
#include "ZombiesPC.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AZombiesGameMode::PostLogin(APlayerController* NewPlayer)
{
	m_PlayerControllers.AddUnique(NewPlayer);
	if(UKismetSystemLibrary::DoesImplementInterface(NewPlayer, UInitable::StaticClass()))
	{
		IInitable::Execute_Init(NewPlayer);
		AZombiesPC* tempPC = Cast<AZombiesPC>(NewPlayer);
		if(tempPC != nullptr)
		{
			//TODO bind to player controller delegates
		}
	}
	
	Super::PostLogin(NewPlayer);
}

void AZombiesGameMode::Logout(AController* Exiting)
{
	m_PlayerControllers.Remove(Exiting);
	AZombiesPC* tempPC = Cast<AZombiesPC>(Exiting);
	if(tempPC != nullptr)
	{
		//TODO unbind from player controller delegates
	}
	Super::Logout(Exiting);
}

AActor* AZombiesGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(m_PlayerStarts.Num() == 0)
	{
		UGameplayStatics:: GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), m_PlayerStarts);
	}
	if(m_PlayerStarts.Num() > 0)
	{
		return m_PlayerStarts[0];
	}
	else
	{
		return nullptr;
	}
}

void AZombiesGameMode::HandleGameRuleSuccess(AGameRuleManager* delegateInstigator)
{
	if(m_GameRuleManagers.Find(delegateInstigator))
	{
		isWin = true;
		EndMatch();
	}
	else
	{
		m_GameRulesLeft--;
		if(m_GameRulesLeft == 0)
		{
			isWin = true;
			EndMatch();
		}
	}
}

void AZombiesGameMode::HandleGameRuleFailure(AGameRuleManager* delegateInstigator)
{
	if(m_GameRuleManagers.Find(delegateInstigator))
	{
		isWin = false;
		EndMatch();
	}
	else
	{
		m_GameRulesLeft++;
	}
}

void AZombiesGameMode::BeginPlay()
{
	// Remove The Player from the world
	UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), 0), true);

	// add a new one of the correct type
	UGameplayStatics::CreatePlayer(GetWorld());
}

void AZombiesGameMode::OnMatchStateSet()
{
	FString output;
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting to start!";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "Match in progress!";
	}
	else if(MatchState == MatchState::WaitingPostMatch)
	{
		output = "in post match waiting!";
	}
	else if(MatchState == MatchState::LeavingMap)
	{
		output = "leaving map!";
	}
	
	Super::OnMatchStateSet();
}

void AZombiesGameMode::HandleMatchIsWaitingToStart()
{
	GetWorld()->GetTimerManager().SetTimer(MatchStartTimer, this, &AGameMode::StartMatch, 0.2f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AZombiesGameMode::HandleMatchHasStarted()
{
	if(m_PlayingPawn != nullptr)
	{
		DefaultPawnClass = m_PlayingPawn;
	}
	for(AController* controller : m_PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}

	m_GameRulesLeft = 0;
	for(TActorIterator<AGameRuleManager> It(GetWorld()); It; ++It)
	{
		m_GameRuleManagers.Add(*It, It->IsMatchEndingRule);
		It->OnGameRuleSuccess.AddDynamic(this, &AZombiesGameMode::HandleGameRuleSuccess);
		It->OnGameRuleFailure.AddDynamic(this, &AZombiesGameMode::HandleGameRuleFailure);
		if(!It->IsMatchEndingRule)
		{
			m_GameRulesLeft++;
		}
		
		if(UKismetSystemLibrary::DoesImplementInterface(*It, UInitable::StaticClass()))
		{
			IInitable::Execute_Init(*It);
		}
	}
	
	Super::HandleMatchHasStarted();
}

void AZombiesGameMode::HandleMatchHasEnded()
{
	for(AController* controller : m_PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchFinished(controller);
		}
	}
	
	Super::HandleMatchHasEnded();
}
