// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_ProjectGameMode.h"
#include "CPP_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPP_ProjectGameMode::ACPP_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
