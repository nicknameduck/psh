// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UIInfo.h"
#include "../../Player/SlotData.h"
#include "ItemDataObject.generated.h"


UCLASS()
class UE20251_API UItemDataObject : public USlotData
{
	GENERATED_BODY()
	
public:
	UItemDataObject();

private:
	FItemData	mItemData;

	// 처음 생성되면 1개는 기본으로 가지기 때문에 기본값을 1로 준다.
	int32		mCount = 1;

	EWidgetMouseState	mItemState = EWidgetMouseState::None;

public:
	EWidgetMouseState GetItemState()	const
	{
		return mItemState;
	}

	void SetItemState(EWidgetMouseState State)
	{
		mItemState = State;
	}

public:
	const FItemData& GetItemData()	const
	{
		return mItemData;
	}

	virtual UTexture2D* GetSlotIcon()
	{
		return mItemData.Icon;
	}

	void SetItemData(const FItemData& Data)
	{
		mItemData = Data;
	}

	void SetItemData(FItemTableInfo* Info)
	{
		mItemData.Type = Info->Type;
		mItemData.SubType = Info->SubType;
		mItemData.ItemName = Info->ItemName;
		mItemData.Desc = Info->Desc;
		mItemData.Price = Info->Price;
		mItemData.Sell = Info->Sell;
		mItemData.Icon = Info->Icon;
		mItemData.Mesh = Info->Mesh;
		mItemData.OptionArray = Info->OptionArray;
	}
};
