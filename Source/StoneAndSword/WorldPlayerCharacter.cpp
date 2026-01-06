// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"

AWorldPlayerCharacter::AWorldPlayerCharacter()
{
	// Disable tick for better performance - this character doesn't need per-frame updates
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure the character mesh (inherited from ACharacter)
	// Position and rotate mesh to align with capsule
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	// Don't rotate when the controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	MovementSpeedMultiplier = 1.0f;
}

void AWorldPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Apply character mesh if set
	if (CharacterMeshAsset && GetMesh())
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshAsset);
	}
	
	// Apply animation blueprint if set
	if (AnimationBlueprintClass && GetMesh())
	{
		GetMesh()->SetAnimInstanceClass(AnimationBlueprintClass);
	}
}

void AWorldPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Validate input component
	if (!PlayerInputComponent)
	{
		return;
	}

	// Set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWorldPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWorldPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AWorldPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AWorldPlayerCharacter::LookUp);
}

void AWorldPlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value * MovementSpeedMultiplier);
	}
}

void AWorldPlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value * MovementSpeedMultiplier);
	}
}

void AWorldPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AWorldPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
