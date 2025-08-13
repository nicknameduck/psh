// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "QuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UQuickSlotWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UQuickSlotWidget(const FObjectInitializer& ObjectInitializer);

protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<class UItemViewerWidget>	mItemViewer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class USlotWidget>>	mSlotArray;

	class UQuickSlotComponent* mQuickSlotComponent = nullptr;

public:
	void InitQuickSlot(class UQuickSlotComponent* Comp);

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void ChangeSlot(UObject* Item, int32 Index);
};
