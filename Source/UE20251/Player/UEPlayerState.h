// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "UEPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API AUEPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AUEPlayerState();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FPlayerData		mInfo;

public:
	const FPlayerData& GetPlayerData() const
	{
		return mInfo;
	}

	void SetPlayerData(const FPlayerInfo& Info);
	void SetCharacterName(const FString& Name);

	bool Damage(float Dmg);
	void AddGold(int32 Gold)
	{
		mInfo.Gold += Gold;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Reset();
	// 클라이언트가 초기화될 때 호출되는 함수
	// UI등 초기 정보를 표현해줄 때 활용한다.
	virtual void ClientInitialize(class AController* C);
};

