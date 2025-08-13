// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "../../UEAssetManager.h"
#include "ItemViewerWidget.h"
#include "SlotWidget.h"
#include "../../Player/InventoryComponent.h"
#include "ItemDataObject.h"
#include "../../Player/UEPlayerState.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("Inventory");
}

void UInventoryWidget::InitInventory(UInventoryComponent* Comp)
{
	mInventoryComponent = Comp;

	if (IsValid(mInventoryComponent))
	{
		mInventoryComponent->mChangeDelegate.AddUObject(this, &UInventoryWidget::ChangeItem);
	}

	for (int32 i = 0; i < mInventoryComponent->GetMaxCount(); ++i)
	{
		// 슬롯 이름을 만들어준다. UI_Slot번호
		FString	SlotName = FString::Printf(TEXT("UI_Slot%d"), i);

		USlotWidget* InventorySlot = Cast<USlotWidget>(GetWidgetFromName(*SlotName));

		InventorySlot->SetSlotIndex(i);
		InventorySlot->SetOwnerWidget(this);
		InventorySlot->SetSlotComponent(mInventoryComponent);

		mSlotArray.Add(InventorySlot);
	}

	RefreshGold();
}

void UInventoryWidget::RefreshGold()
{
	APlayerController* PC = GetOwningPlayer();

	if (PC)
	{
		AUEPlayerState* State = PC->GetPlayerState<AUEPlayerState>();
		State->GetPlayerData().Gold;
		
		mGoldText->SetText(FText::FromString(FString::Printf(TEXT("골드 : %d"), State->GetPlayerData().Gold)));
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mGoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Gold")));
	mItemViewer = Cast<UItemViewerWidget>(GetWidgetFromName(TEXT("UI_ItemViewer")));

	mCloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::CloseButtonClick);
	mTitleBar->OnPressed.AddDynamic(this, &UInventoryWidget::TitleBarPress);
	mTitleBar->OnReleased.AddDynamic(this, &UInventoryWidget::TitleBarRelease);
}

void UInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInventoryWidget::OpenUI()
{
	ESlateVisibility CurrentVisibility = GetVisibility();

	switch (CurrentVisibility)
	{
		case ESlateVisibility::Visible:
			{
				SetVisibility(ESlateVisibility::Collapsed);
			}
			break;
		case ESlateVisibility::Collapsed:
		case ESlateVisibility::Hidden:
		case ESlateVisibility::HitTestInvisible:
		case ESlateVisibility::SelfHitTestInvisible:
			{
				SetVisibility(ESlateVisibility::Visible);
			}
			break;
		default:
			break;
	}
}

void UInventoryWidget::ChangeItem(UObject* Item, int32 Index)
{
	mSlotArray[Index]->ChangeItem(Cast<UItemDataObject>(Item));
	RefreshGold();
}

void UInventoryWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryWidget::TitleBarPress()
{
	UBaseUserWidget* ParentWidget = Cast<UBaseUserWidget>(mParentWidget);

	if (ParentWidget)
	{
		ParentWidget->SetDragWidget(this);
		ParentWidget->SetFocusWidget(this);
	}
}

void UInventoryWidget::TitleBarRelease()
{
	UBaseUserWidget* ParentWidget = Cast<UBaseUserWidget>(mParentWidget);

	if (ParentWidget)
	{
		ParentWidget->SetDragWidget(nullptr);
	}
}
