// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"

AWorldPlayerCharacter::AWorldPlayerCharacter()
{
	// Disable tick for better performance - this character doesn't need per-frame updates
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure the character mesh (inherited from ACharacter) - body mesh
	// Position mesh below capsule
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	// By default, owner won't see this mesh (first-person - don't see own body unless enabled)
	GetMesh()->SetOwnerNoSee(true);
	
	// Configure controller rotation for first-person
	// Character rotates with camera yaw (looking left/right)
	bUseControllerRotationPitch = false; // Don't tilt character when looking up/down
	bUseControllerRotationYaw = true;    // Rotate character when turning camera left/right
	bUseControllerRotationRoll = false;

	// Configure character movement for first-person
	GetCharacterMovement()->bOrientRotationToMovement = false; // Don't rotate to movement direction in FPS
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // Faster rotation for FPS
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Create first-person camera
	// Attached to mesh at eye level (socket "head" if exists, or fixed offset)
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f)); // Eye height (adjust as needed)
	FirstPersonCamera->bUsePawnControlRotation = true; // Camera follows controller rotation

	// Initialize properties
	MovementSpeedMultiplier = 1.0f;
	bShowBodyInFirstPerson = false; // Default: hide body, only show arms if set
}

void AWorldPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Configure body mesh visibility for first-person
	if (GetMesh())
	{
		GetMesh()->SetOwnerNoSee(!bShowBodyInFirstPerson);
	}
	
	// Apply first-person arms mesh if set
	if (FirstPersonArmsMesh && GetMesh())
	{
		// Note: For proper first-person arms, you would typically create a separate
		// USkeletalMeshComponent attached to the camera. This is a simplified approach
		// where we're using the main mesh. For production, consider creating a dedicated
		// FirstPersonArmsMesh component attached to FirstPersonCamera.
		GetMesh()->SetSkeletalMesh(FirstPersonArmsMesh);
		GetMesh()->SetOwnerNoSee(false); // Show arms mesh to owner
		GetMesh()->SetOnlyOwnerSee(true); // Hide arms from other players
	}
	
	// Apply animation blueprint if set
	if (FirstPersonArmsAnimationClass && GetMesh())
	{
		GetMesh()->SetAnimInstanceClass(FirstPersonArmsAnimationClass);
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
