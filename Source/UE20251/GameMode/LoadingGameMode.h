// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "LoadingGameMode.generated.h"

UCLASS()
class UE20251_API ALoadingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoadingGameMode();

protected:
	int32		mJob;
	FString		mMapName;
	FString		mMapPath;
	FString		mPlayerName;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void InitGameState();
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);

protected:
	virtual void BeginPlay() override;

private:
	void LoadingAsyncComplete(const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result);
};
