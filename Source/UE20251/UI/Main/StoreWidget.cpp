// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreWidget.h"
#include "ItemDataObject.h"
#include "StoreItemWidget.h"
#include "../../UEAssetManager.h"
#include "ItemViewerWidget.h"
#include "../../Player/UEPlayerState.h"
#include "../../Player/PlayerCharacter.h"
#include "../../Player/InventoryComponent.h"

UStoreWidget::UStoreWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("Store");
}

void UStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mClearButton = Cast<UButton>(GetWidgetFromName(TEXT("ClearButton")));
	mBuyButton = Cast<UButton>(GetWidgetFromName(TEXT("BuyButton")));
	mItemList = Cast<UListView>(GetWidgetFromName(TEXT("ItemList")));
	mItemViewer = Cast<UItemViewerWidget>(GetWidgetFromName(TEXT("UI_ItemViewer")));

	mCloseButton->OnClicked.AddDynamic(this, &UStoreWidget::CloseButtonClick);
	mTitleBar->OnPressed.AddDynamic(this, &UStoreWidget::TitleBarPress);
	mTitleBar->OnReleased.AddDynamic(this, &UStoreWidget::TitleBarRelease);

	FName	ItemNames[4] =
	{
		TEXT("WoodSword"),
		TEXT("LongSword"),
		TEXT("SmallHPPotion"),
		TEXT("SmallMPPotion")
	};

	for (int32 i = 0; i < 10000; ++i)
	{
		int32	Index = FMath::RandRange(0, 3);

		FItemTableInfo* Info = UUEAssetManager::Get().FindDataTableRow<FItemTableInfo>(TEXT("DTItemInfo"), ItemNames[Index]);

		if (!Info)
			continue;

		UItemDataObject* ItemObj = NewObject<UItemDataObject>();

		ItemObj->SetItemData(Info);

		mItemList->AddItem(ItemObj);
	}

	mItemList->OnItemSelectionChanged().AddUObject(this, &UStoreWidget::ItemSelect);
	mItemList->OnItemIsHoveredChanged().AddUObject(this, &UStoreWidget::ItemHovered);
	mItemList->OnItemDoubleClicked().AddUObject(this, &UStoreWidget::ItemRemove);

	mClearButton->OnClicked.AddDynamic(this, &UStoreWidget::ClearAllItem);

	mBuyButton->OnClicked.AddDynamic(this, &UStoreWidget::BuyItem);
}

void UStoreWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UStoreWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply	result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	// 마우스가 올라간 아이템이 있을 경우
	if (IsValid(mHoveredItem))
	{
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(mItemViewer->Slot);

		if (IsValid(PanelSlot))
		{
			// 스크린 공간에서의 마우스 위치를 얻어온다.
			FVector2D	MousePos = InMouseEvent.GetScreenSpacePosition();

			// 스크린 공간에서의 마우스 위치를 위젯 공간에서의 마우스 위치로 변환한다..
			FVector2D	WidgetMousePos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, MousePos);

			PanelSlot->SetPosition(WidgetMousePos);
		}
	}

	return result;
}

void UStoreWidget::ItemSelect(UObject* Item)
{
	// 기존에 선택되었던 아이템이 있을 경우
	if (IsValid(mSelectItem))
	{
		// 아이템 상태를 변경한다.
		mSelectItem->SetItemState(EWidgetMouseState::None);

		UStoreItemWidget* CurrentWidget = mItemList->GetEntryWidgetFromItem<UStoreItemWidget>(mSelectItem);

		if (IsValid(CurrentWidget))
		{
			CurrentWidget->SetMouseState(EWidgetMouseState::None);
		}
	}

	// 선택된 아이템을 교체한다.
	mSelectItem = Cast<UItemDataObject>(Item);

	// 선택된 아이템이 있을 경우
	if (IsValid(mSelectItem))
	{
		// 아이템 상태를 변경한다.
		mSelectItem->SetItemState(EWidgetMouseState::Select);

		UStoreItemWidget* CurrentWidget = mItemList->GetEntryWidgetFromItem<UStoreItemWidget>(mSelectItem);

		if (IsValid(CurrentWidget))
		{
			CurrentWidget->SetMouseState(EWidgetMouseState::Select);
		}
	}
}

void UStoreWidget::ItemHovered(UObject* Item, bool IsHovered)
{
	UItemDataObject* CurrentItem = Cast<UItemDataObject>(Item);

	// 현재 아이템 정보를 출력하고 있는 ItemWidget을 얻어온다.
	UStoreItemWidget* CurrentWidget = mItemList->GetEntryWidgetFromItem<UStoreItemWidget>(Item);

	if (!IsValid(CurrentWidget))
	{
		return;
	}

	// 현재 인자로 들어온 아이템 위에 Hovered 상태가 되었을 경우
	if (IsHovered)
	{
		// 마우스가 올라간 아이템을 교체한다.
		mHoveredItem = CurrentItem;

		// 기존에 선택된 아이템에 마우스가 올라간 경우라면 그대로 선택으로 유지해야 한다.
		// 그렇기 때문에 선택된 아이템과 다를 경우에만 Hovered로 처리한다.
		if (mSelectItem != CurrentItem)
		{
			// 아이템 상태를 변경한다.
			CurrentItem->SetItemState(EWidgetMouseState::Hovered);
			CurrentWidget->SetMouseState(EWidgetMouseState::Hovered);
		}

		mItemViewer->SetVisibility(ESlateVisibility::HitTestInvisible);

		mItemViewer->SetItemInfo(CurrentItem->GetItemData());
	}

	// 기존에 Hovered상태에 있던 아이템에서 마우스가 빠져나갈 경우
	else
	{
		mHoveredItem = nullptr;

		if (mSelectItem != CurrentItem)
		{
			// 아이템 상태를 변경한다.
			CurrentItem->SetItemState(EWidgetMouseState::None);
			CurrentWidget->SetMouseState(EWidgetMouseState::None);
		}

		mItemViewer->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UStoreWidget::ItemRemove(UObject* Item)
{
	// 기존에 선택한 아이템이 있을 경우
	if (IsValid(mSelectItem))
	{
		mSelectItem->SetItemState(EWidgetMouseState::None);

		UStoreItemWidget* CurrentWidget = mItemList->GetEntryWidgetFromItem<UStoreItemWidget>(mSelectItem);

		if (IsValid(CurrentWidget))
		{
			CurrentWidget->SetMouseState(EWidgetMouseState::None);
		}
	}

	mSelectItem = nullptr;

	mItemList->RemoveItem(Item);
}

void UStoreWidget::ClearAllItem()
{
	mSelectItem = nullptr;
	mHoveredItem = nullptr;

	// 리스트 안에 있는 모든 아이템을 제거한다.
	mItemList->ClearListItems();
}

void UStoreWidget::BuyItem()
{
	// 구매하기 위해 선택한 아이템이 없을 경우 반환한다.
	if (!IsValid(mSelectItem))
	{
		return;
	}

	// 위젯을 소유한 플레이어 컨트롤러를 가져온다.
	//APlayerController* PC = GetWorld()->GetFirstPlayerController();
	APlayerController* PC = GetOwningPlayer();

	if (PC)
	{
		AUEPlayerState* State = PC->GetPlayerState<AUEPlayerState>();

		if (State)
		{
			APlayerCharacter* Character = PC->GetPawn<APlayerCharacter>();

			UInventoryComponent* Inventory = Character->GetInventoryComponent();

			// 가지고 있는 돈이 부족하여 구매할 수 없는 경우
			if (mSelectItem->GetItemData().Price > State->GetPlayerData().Gold)
			{
				UE_LOG(LogUE20251, Warning, TEXT("보유금액이 부족합니다."));
			}

			else if (Inventory->IsFull())
			{
				UE_LOG(LogUE20251, Warning, TEXT("인벤토리 공간이 부족합니다."));
			}

			else
			{
				// 보유금액을 차감한다.
				State->AddGold(-mSelectItem->GetItemData().Price);

				Inventory->AddItem(mSelectItem->GetItemData());
			}
		}
	}
}

void UStoreWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UStoreWidget::TitleBarPress()
{
	UBaseUserWidget* ParentWidget = Cast<UBaseUserWidget>(mParentWidget);

	if (ParentWidget)
	{
		ParentWidget->SetDragWidget(this);
		ParentWidget->SetFocusWidget(this);
	}
}

void UStoreWidget::TitleBarRelease()
{
	UBaseUserWidget* ParentWidget = Cast<UBaseUserWidget>(mParentWidget);

	if (ParentWidget)
	{
		ParentWidget->SetDragWidget(nullptr);
	}
}

void UStoreWidget::OpenUI()
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