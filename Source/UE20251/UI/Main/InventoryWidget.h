// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UInventoryWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mTitleBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mCloseButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mGoldText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UItemViewerWidget>	mItemViewer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class USlotWidget>>	mSlotArray;

	class UInventoryComponent* mInventoryComponent = nullptr;

public:
	void InitInventory(class UInventoryComponent* Comp);
	void RefreshGold();

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	UFUNCTION(BlueprintCallable)
	void OpenUI();

	void ChangeItem(UObject* Item, int32 Index);

	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void TitleBarPress();

	UFUNCTION()
	void TitleBarRelease();

};
