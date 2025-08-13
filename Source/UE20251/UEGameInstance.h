// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "UEGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UUEGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUEGameInstance();
	
public:
	virtual void Init();
	virtual void Shutdown();
};
