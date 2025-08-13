// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "DataSystem.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UDataSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UDataSystem();

private:
	TObjectPtr<UDataTable>	mPlayerAnimData;

public:
	FPlayerAnimInfo* FindPlayerAnimData(const FName& Name)	const;
	void GetAllPlayerAnimData(TArray<FPlayerAnimInfo*>& AnimArray)	const;
};
