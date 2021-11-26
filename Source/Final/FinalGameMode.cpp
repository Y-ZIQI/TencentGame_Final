// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalGameMode.h"
#include "FinalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFinalGameMode::AFinalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Actors/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
