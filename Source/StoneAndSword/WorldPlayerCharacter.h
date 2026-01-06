// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WorldPlayerCharacter.generated.h"

// Forward declarations
class UCameraComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class UAnimInstance;

/**
 * Player character for exploring the open world.
 * Provides third-person camera controls, WASD movement, and jump capability.
 * Supports skeletal mesh and animations that can be easily set from store assets.
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

	/** Get the camera component */
	UFUNCTION(BlueprintPure, Category = "Camera")
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	/** Get the camera boom component */
	UFUNCTION(BlueprintPure, Category = "Camera")
	USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Get the character mesh component */
	UFUNCTION(BlueprintPure, Category = "Mesh")
	USkeletalMeshComponent* GetCharacterMesh() const { return GetMesh(); }

protected:
	/** Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** 
	 * Skeletal mesh to use for the character.
	 * Can be set to any mesh from UE Marketplace, Mixamo, or custom assets.
	 * If not set, character will be invisible but still functional.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USkeletalMesh> CharacterMeshAsset;

	/** 
	 * Animation Blueprint class to use for character animations.
	 * Can be set to animation blueprints from store assets or custom animations.
	 * Supports idle, walk, run, jump animations.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSubclassOf<UAnimInstance> AnimationBlueprintClass;

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
