// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformGameMode.h"
#include "PlatformCharacter.h"
#include "PlatformGameState.h"
#include "PlatformPlayerState.h"

APlatformGameMode::APlatformGameMode()
{
	DefaultPawnClass = APlatformCharacter::StaticClass();
	GameStateClass = APlatformGameState::StaticClass();
	PlayerStateClass = APlatformPlayerState::StaticClass();
}
