// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Evil_FiGameMode.h"
#include "Contents/Character/Evil_FiCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEvil_FiGameMode::AEvil_FiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
