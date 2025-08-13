// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "../../Player/QuickSlotComponent.h"
#include "SlotWidget.h"

UQuickSlotWidget::UQuickSlotWidget(const FObjectInitializer& ObjectInitializer)	:
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("QuickSlot");
}

void UQuickSlotWidget::InitQuickSlot(UQuickSlotComponent* Comp)
{
	mQuickSlotComponent = Comp;

	if (IsValid(mQuickSlotComponent))
	{
		mQuickSlotComponent->mChangeDelegate.AddUObject(this, &UQuickSlotWidget::ChangeSlot);
	}

	for (int32 i = 0; i < mQuickSlotComponent->GetMaxCount(); ++i)
	{
		// 슬롯 이름을 만들어준다. UI_Slot번호
		FString	SlotName = FString::Printf(TEXT("UI_QuickSlot_%d"), i);

		UE_LOG(LogUE20251, Warning, TEXT("%s : %d"), *SlotName, i);

		USlotWidget* QuickSlot = Cast<USlotWidget>(GetWidgetFromName(*SlotName));

		QuickSlot->SetSlotIndex(i);
		QuickSlot->SetOwnerWidget(this);
		QuickSlot->SetSlotComponent(mQuickSlotComponent);

		mSlotArray.Add(QuickSlot);
	}
}

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//mItemViewer = Cast<UItemViewerWidget>(GetWidgetFromName(TEXT("UI_ItemViewer")));
}

void UQuickSlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UQuickSlotWidget::ChangeSlot(UObject* Item, int32 Index)
{
	mSlotArray[Index]->ChangeItem(Cast<USlotData>(Item));
}
