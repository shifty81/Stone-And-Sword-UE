// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WorldPlayerCharacter.generated.h"

// Forward declarations
class UCameraComponent;

/**
 * Player character for exploring the open world in first-person view.
 * Provides first-person camera controls, WASD movement, and jump capability.
 * Supports optional visible arms/hands mesh with animations from store assets.
 * Optimized for performance with tick disabled.
 */
UCLASS()
class STONEANDSWORD_API AWorldPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWorldPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Get the first-person camera component */
	UFUNCTION(BlueprintPure, Category = "Camera")
	UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

	/** Get the character mesh component (body - hidden in first person) */
	UFUNCTION(BlueprintPure, Category = "Mesh")
	USkeletalMeshComponent* GetCharacterMesh() const { return GetMesh(); }

protected:
	/** First-person camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	/** 
	 * Optional first-person arms/hands mesh.
	 * Can be set to any mesh from UE Marketplace, Mixamo, or custom assets.
	 * Shows in first-person view (hands/arms holding weapons, etc.)
	 * If not set, pure first-person view without visible body parts.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMesh> FirstPersonArmsMesh;

	/** 
	 * Animation Blueprint class for first-person arms animations.
	 * Can be set to animation blueprints from store assets or custom animations.
	 * Supports idle, walk, run, jump animations for arms/hands.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSubclassOf<UAnimInstance> FirstPersonArmsAnimationClass;

	/** 
	 * Whether to show the full body mesh in first person.
	 * If false, body is hidden and only FirstPersonArmsMesh is visible.
	 * If true, full body is visible (can see own legs, etc.)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	bool bShowBodyInFirstPerson;

	/** Movement speed multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeedMultiplier;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for mouse look/turn input */
	void Turn(float Value);

	/** Called for mouse look up/down input */
	void LookUp(float Value);
};
