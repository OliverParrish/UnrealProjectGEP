// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiesPC.h"



#include "GetPlayerCharacter.h"
#include "ZombiesPChar.h"
#include "GameFramework/GameModeBase.h"
#include "GEPProject/Public/Inputable.h"
#include "Kismet/GameplayStatics.h"

void AZombiesPC::SetupInputComponent()
{
	// always call this
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &AZombiesPC::JumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &AZombiesPC::JumpReleased);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AZombiesPC::FirePressed);
	InputComponent->BindAction("Fire", IE_Released, this, &AZombiesPC::FireReleased);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AZombiesPC::SprintPressed);
	InputComponent->BindAction("Sprint", IE_Released, this, &AZombiesPC::SprintReleased);
	InputComponent->BindAction("Reload", IE_Pressed, this, &AZombiesPC::ReloadPressed);

	InputComponent->BindAxis("MoveForward", this, &AZombiesPC::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AZombiesPC::MoveRight);
	InputComponent->BindAxis("LookUp", this, &AZombiesPC::LookUp);
	InputComponent->BindAxis("Turn", this, &AZombiesPC::Turn);

	InputComponent->BindAxis("LookUpRate", this, &AZombiesPC::LookUpAtRate);
	InputComponent->BindAxis("TurnRate", this, &AZombiesPC::TurnAtRate);
}

void AZombiesPC::Init_Implementation()
{
	if(GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AZombiesPC::Handle_MatchStarted_Implementation()
{

	UWorld* const World = GetWorld();

	AActor* tempStart = UGameplayStatics::GetGameMode(World)->FindPlayerStart(this);
	FVector spawnLocation = ((tempStart != nullptr) ? tempStart->GetActorLocation() : FVector::ZeroVector);
	FRotator spawnRotation = ((tempStart != nullptr) ? tempStart->GetActorRotation() : FRotator::ZeroRotator);

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = World->SpawnActor<APawn>(UGameplayStatics::GetGameMode(World)->DefaultPawnClass, spawnLocation,
		spawnRotation, ActorSpawnParameters);

	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInitable::StaticClass()))
	{
		IInitable::Execute_Init(tempPawn);
	}
	
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UGetPlayerCharacter::StaticClass()))
	{
		AZombiesPChar* tempChar = IGetPlayerCharacter::Execute_ReturnCharacter(tempPawn);
		tempChar->OnHealthUpdate.AddDynamic(this, &AZombiesPC::HealthBarUpdate);
		tempChar->OnPlayerDeath.AddDynamic(this, &AZombiesPC::OnCharDied);
	}

	Possess(tempPawn);
}

void AZombiesPC::Handle_MatchFinished_Implementation()
{
	//SetInputMode(FInputModeUIOnly());
}

void AZombiesPC::HealthBarUpdate(float update)
{
	OnHealthBarUpdate.Broadcast(update);
}

void AZombiesPC::OnCharDied_Implementation(AZombiesPChar* Char)
{
	
}

void AZombiesPC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AZombiesPC::JumpPressed()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_JumpPressed(tempPawn);
	}
}

void AZombiesPC::JumpReleased()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_JumpReleased(tempPawn);
	}
}

void AZombiesPC::FirePressed()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_FirePressed(tempPawn);
	}
}

void AZombiesPC::FireReleased()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_FireReleased(tempPawn);
	}
}

void AZombiesPC::SprintPressed()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_SprintPressed(tempPawn);
	}
}

void AZombiesPC::SprintReleased()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_SprintReleased(tempPawn);
	}
}

void AZombiesPC::ReloadPressed()
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_ReloadPressed(tempPawn);
	}
}

void AZombiesPC::MoveForward(float value)
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_MoveForward(tempPawn, value);
	}
}

void AZombiesPC::MoveRight(float value)
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_MoveRight(tempPawn, value);
	}
}

void AZombiesPC::LookUp(float value)
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_LookUp(tempPawn, value);
	}
}

void AZombiesPC::Turn(float value)
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Turn(tempPawn, value);
	}
}

void AZombiesPC::LookUpAtRate(float value)
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_LookUpAtRate(tempPawn, value);
	}
}

void AZombiesPC::TurnAtRate(float value)
{
	APawn* tempPawn = GetPawn();
	if(UKismetSystemLibrary::DoesImplementInterface(tempPawn, UInputable::StaticClass()))
	{
		IInputable::Execute_TurnAtRate(tempPawn, value);
	}
}
