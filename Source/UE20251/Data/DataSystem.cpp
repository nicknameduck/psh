// Fill out your copyright notice in the Description page of Project Settings.


#include "DataSystem.h"

UDataSystem::UDataSystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		PlayerAnimTable(TEXT("/Script/Engine.DataTable'/Game/Player/DTPlayerAnim.DTPlayerAnim'"));

	if (PlayerAnimTable.Succeeded())
		mPlayerAnimData = PlayerAnimTable.Object;
}

FPlayerAnimInfo* UDataSystem::FindPlayerAnimData(const FName& Name)	const
{
	return mPlayerAnimData->FindRow<FPlayerAnimInfo>(Name, TEXT(""));
}

void UDataSystem::GetAllPlayerAnimData(TArray<FPlayerAnimInfo*>& AnimArray)	const
{
	mPlayerAnimData->GetAllRows<FPlayerAnimInfo>(TEXT(""), AnimArray);
}
