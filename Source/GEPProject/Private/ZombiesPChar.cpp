// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombiesPChar.h"

#include "Reloadable.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GEPProject/Fireable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GEPProject/HealthComponent.h"

// Sets default values
AZombiesPChar::AZombiesPChar()
{
	CamBoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Cam Boom Arm")); // Create component
	CamBoomArm->SetupAttachment(RootComponent); // Attach to root component
	CamBoomArm->TargetArmLength = 300; // Sets the length of the camera from the player
	CamBoomArm->bUsePawnControlRotation = true; // Locks boom arm behind character

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); // Create Camera Component
	CameraComponent->SetupAttachment(CamBoomArm, USpringArmComponent::SocketName); // Attach to the Spring Arm Component
	CameraComponent->bUsePawnControlRotation = false; // Stop Cam rotating relative to the boom arm

	// Stops the character mesh from rotating - Only rotates Cam on these axes
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Changes character rotation based on which direction Key Pressed
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0); // Character rotation rate

	WeaponSocketComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSocketComponent"));
	WeaponSocketComponent->SetupAttachment(ACharacter::GetMesh(), "RightHandSocket");
	
	m_ChildActor_Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunSlot"));
	m_ChildActor_Gun->SetupAttachment(WeaponSocketComponent);
	m_ChildActor_Gun->CreateChildActor();

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	IsSprinting = false;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AZombiesPChar::Init_Implementation()
{
	HealthComponent->OnHealthUpdate.AddDynamic(this, &AZombiesPChar::HealthUpdate);
	HealthComponent->OnDeath.AddDynamic(this, &AZombiesPChar::Death);
	HealthComponent->Init();

	HealthUpdate(1);
}

void AZombiesPChar::JumpPressed_Implementation()
{
	Jump();
}

void AZombiesPChar::JumpReleased_Implementation()
{
}

void AZombiesPChar::FirePressed_Implementation()
{
	AActor* child = m_ChildActor_Gun->GetChildActor();
	if(UKismetSystemLibrary::DoesImplementInterface(child, UFireable::StaticClass()))
	{
		IFireable::Execute_Fire(child, this, this);
	}
}

void AZombiesPChar::FireReleased_Implementation()
{
	
}

void AZombiesPChar::SprintPressed_Implementation()
{
	if(!IsSprinting)
	{
		IsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}

void AZombiesPChar::SprintReleased_Implementation()
{			
	if(IsSprinting)
	{
		IsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 250.f;
	}
}

void AZombiesPChar::ReloadPressed_Implementation()
{
	AActor* child = m_ChildActor_Gun->GetChildActor();
	if(UKismetSystemLibrary::DoesImplementInterface(child, UReloadable::StaticClass()))
	{
		IReloadable::Execute_Reload(child, this, this);
	}
}

void AZombiesPChar::MoveForward_Implementation(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X); // Gets Forward Vector
		AddMovementInput(Direction, value);
	}
}

void AZombiesPChar::MoveRight_Implementation(float value)
{
	if (Controller != nullptr && value != 0.f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y); // Gets Forward Vector
		AddMovementInput(Direction, value);
	}
}

void AZombiesPChar::LookUp_Implementation(float value)
{
	if(value != 0.f)
	{
		AddControllerPitchInput(value);
	}
}

void AZombiesPChar::Turn_Implementation(float value)
{
	if(value != 0.f)
	{
		AddControllerYawInput(value);
	}
}

void AZombiesPChar::LookUpAtRate_Implementation(float value)
{
	if(value != 0.f)
	{
		AddControllerPitchInput(value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AZombiesPChar::TurnAtRate_Implementation(float value)
{
	if(value != 0.f)
	{
		AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

AZombiesPChar* AZombiesPChar::ReturnCharacter_Implementation()
{
	return this;
}

void AZombiesPChar::Death_Implementation(AController* DamageInstigator)
{
	//Handle Death stuff
	GetCapsuleComponent()->SetCollisionProfileName("IgnoreOnlyPawn", false);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetMesh()->SetCollisionProfileName("Ragdoll", false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	GetMesh()->SetSimulatePhysics(true);
	GetController()->UnPossess();

	OnPlayerDeath.Broadcast(this);
}

void AZombiesPChar::HealthUpdate(float healthUpdate)
{
	OnHealthUpdate.Broadcast(healthUpdate);
}

