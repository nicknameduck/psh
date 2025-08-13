// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "../Player/Warrior.h"
#include "../Player/Magicion.h"
#include "../Player/MainPlayerController.h"

ADefaultGameMode::ADefaultGameMode()
{
	//DefaultPawnClass = AWarrior::StaticClass();
	DefaultPawnClass = AMagicion::StaticClass();

	PlayerControllerClass = AMainPlayerController::StaticClass();
}

APlayerController* ADefaultGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* PlayerCtrl = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	int32	Job = 0;
	FString	PlayerName;

	FParse::Value(*Options, TEXT("Job="), Job);
	FParse::Value(*Options, TEXT("PlayerName="), PlayerName);

	EPlayerJob	PlayerJob = (EPlayerJob)Job;

	switch (PlayerJob)
	{
	case EPlayerJob::Warrior:
		DefaultPawnClass = AWarrior::StaticClass();
		break;
	case EPlayerJob::Magician:
		DefaultPawnClass = AMagicion::StaticClass();
		break;
	case EPlayerJob::Archer:
		break;
	case EPlayerJob::Assassin:
		break;
	}

	AMainPlayerController* MainController = Cast<AMainPlayerController>(PlayerCtrl);

	if (IsValid(MainController))
	{
		MainController->SetPlayerName(PlayerName);
	}


	return PlayerCtrl;
}
