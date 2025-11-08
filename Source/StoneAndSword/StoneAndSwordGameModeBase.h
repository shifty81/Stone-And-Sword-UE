// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StoneAndSwordGameModeBase.generated.h"

/**
 * Game Mode for Stone and Sword open world game.
 * Manages game rules, flow, and automatic world setup.
 * Sets the default pawn to WorldPlayerCharacter.
 */
UCLASS()
class STONEANDSWORD_API AStoneAndSwordGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStoneAndSwordGameModeBase();

protected:
	virtual void StartPlay() override;

	/** Whether to automatically setup the world with WorldSetupManager */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup")
	bool bAutoSpawnWorldSetupManager;

	/** Get the spawned world setup manager, if any */
	UFUNCTION(BlueprintPure, Category = "World Setup")
	AWorldSetupManager* GetWorldSetupManager() const { return WorldSetupManager; }

private:
	/** Reference to the spawned WorldSetupManager */
	UPROPERTY()
	TObjectPtr<AWorldSetupManager> WorldSetupManager;
};
