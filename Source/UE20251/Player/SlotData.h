// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "SlotData.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API USlotData : public UObject
{
	GENERATED_BODY()
	
public:
	USlotData();

protected:
	int32	mSlotIndex = -1;

public:
	void SetSlotIndex(int32 Index)
	{
		mSlotIndex = Index;
	}

	int32 GetSlotIndex()	const
	{
		return mSlotIndex;
	}

	virtual UTexture2D* GetSlotIcon();
};
