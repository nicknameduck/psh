// Fill out your copyright notice in the Description page of Project Settings.


#include "UEGameInstance.h"
#include "UI/UIManager.h"

UUEGameInstance::UUEGameInstance()
{
}

void UUEGameInstance::Init()
{
	Super::Init();
}

void UUEGameInstance::Shutdown()
{
	Super::Shutdown();

	CUIManager::DestroyInst();
}
