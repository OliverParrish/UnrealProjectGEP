// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(InPawn->GetClass()->ImplementsInterface(UGetEnemyAI::StaticClass()))
	{
		AEnemyAI* EnemyAI = IGetEnemyAI::Execute_GetEnemyAI(InPawn);
		if(EnemyAI)
		{
			RunBehaviorTree(EnemyAI->BehaviorTree);
			GetBlackboardComponent()->SetValueAsFloat(RangeKeyName, EnemyAI->m_Range);
			GetBlackboardComponent()->SetValueAsFloat(AttackCooldownKeyName, EnemyAI->m_AttackCooldown);
		}
	}
}



