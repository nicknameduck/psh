// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "ItemViewerWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UItemViewerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UItemViewerWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mItemDesc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mItemPrice;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mItemSell;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UScrollBox>	mOptionScroll;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void SetItemInfo(const FItemData& Data);
};
