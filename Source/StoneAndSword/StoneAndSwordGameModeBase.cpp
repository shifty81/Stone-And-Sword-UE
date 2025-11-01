// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoneAndSwordGameModeBase.h"
#include "WorldPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStoneAndSwordGameModeBase::AStoneAndSwordGameModeBase()
{
	// Set default pawn class to our character
	DefaultPawnClass = AWorldPlayerCharacter::StaticClass();
}
