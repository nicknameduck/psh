// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlayerState.h"
#include "../UI/UIManager.h"
#include "../UI/Main/PlayerHUDWidget.h"

AUEPlayerState::AUEPlayerState()
{
	mInfo.Name = TEXT("Player");
}

void AUEPlayerState::SetPlayerData(const FPlayerInfo& Info)
{
	mInfo.Job = Info.Job;
	mInfo.Attack = Info.Attack;
	mInfo.Defense = Info.Defense;
	mInfo.HP = Info.HP;
	mInfo.HPMax = Info.HP;
	mInfo.MP = Info.MP;
	mInfo.MPMax = Info.MP;
	mInfo.AttackRange = Info.AttackRange;
	mInfo.AttackSpeed = Info.AttackSpeed;
	mInfo.MoveSpeed = Info.MoveSpeed;
}

void AUEPlayerState::SetCharacterName(const FString& Name)
{
	mInfo.Name = Name;
}

bool AUEPlayerState::Damage(float Dmg)
{
	bool	Alive = true;

	mInfo.HP -= Dmg;

	if (mInfo.HP <= 0.f)
	{
		mInfo.HP = 0.f;
		Alive = false;
	}

	UPlayerHUDWidget* Widget = CUIManager::GetInst()->FindWidget<UPlayerHUDWidget>(TEXT("PlayerHUD"));

	if (Widget)
	{
		Widget->SetHPPercent(mInfo.HP / (float)mInfo.HPMax);
	}

	return Alive;
}

void AUEPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogUE20251, Warning, TEXT("PlayerState BeginPlay"));
}

void AUEPlayerState::Reset()
{
	Super::Reset();
}

// 클라이언트가 초기화될 때 호출되는 함수
// UI등 초기 정보를 표현해줄 때 활용한다.
void AUEPlayerState::ClientInitialize(class AController* C)
{
	Super::ClientInitialize(C);
}