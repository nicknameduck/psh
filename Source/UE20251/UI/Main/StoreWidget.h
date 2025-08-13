// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "StoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UStoreWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UStoreWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mTitleBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mCloseButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mClearButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UListView>	mItemList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mBuyButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UItemViewerWidget>	mItemViewer;

	class UItemDataObject* mHoveredItem = nullptr;
	class UItemDataObject* mSelectItem = nullptr;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

protected:
	UFUNCTION()
	void ItemSelect(UObject* Item);

	UFUNCTION()
	void ItemHovered(UObject* Item, bool IsHovered);

	UFUNCTION()
	void ItemRemove(UObject* Item);

	UFUNCTION()
	void ClearAllItem();

	UFUNCTION()
	void BuyItem();

	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void TitleBarPress();

	UFUNCTION()
	void TitleBarRelease();

public:
	UFUNCTION(BlueprintCallable)
	void OpenUI();
};
