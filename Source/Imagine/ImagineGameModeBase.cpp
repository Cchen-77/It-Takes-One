// Copyright Epic Games, Inc. All Rights Reserved.


#include "ImagineGameModeBase.h"
#include"Player/IMCharacter.h"
#include"Player/IMPlayerController.h"
AImagineGameModeBase::AImagineGameModeBase()
{
	DefaultPawnClass = AIMCharacter::StaticClass();
	PlayerControllerClass = AIMPlayerController::StaticClass();
}
