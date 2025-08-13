// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"


UCLASS()
class UE20251_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USlotWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UIconWidget>	mSlotIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBorder>	mSlotBack;

	class UBaseUserWidget* mOwnerWidget = nullptr;

	int32		mSlotIndex = 0;

	class USlotComponent* mSlotComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<USlotWidget>	mDragWidgetClass;

public:
	void SetOwnerWidget(class UBaseUserWidget* OwnerWidget);

	void SetSlotIndex(int32 Index);

	void SetSlotComponent(class USlotComponent* SlotComponent)
	{
		mSlotComponent = SlotComponent;
	}

protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	void ChangeItem(class USlotData* Item);
};
