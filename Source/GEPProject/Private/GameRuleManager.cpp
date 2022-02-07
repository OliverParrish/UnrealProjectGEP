// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRuleManager.h"

// Sets default values
AGameRuleManager::AGameRuleManager()
{
	IsMatchEndingRule = false;
}

void AGameRuleManager::BroadcastGameRuleSuccess()
{
	OnGameRuleSuccess.Broadcast(this);
}

void AGameRuleManager::BroadcastGameRuleFailure()
{
	OnGameRuleFailure.Broadcast(this);
}



