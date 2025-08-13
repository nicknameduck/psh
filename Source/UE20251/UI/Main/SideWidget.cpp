// Fill out your copyright notice in the Description page of Project Settings.


#include "SideWidget.h"
#include "InventoryWidget.h"
#include "PlayerStatusWidget.h"
#include "StoreWidget.h"
#include "../UIManager.h"

USideWidget::USideWidget(const FObjectInitializer& ObjectInitializer)
	: UBaseUserWidget(ObjectInitializer)
{
	
}

void USideWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mInventory = Cast<UButton>(GetWidgetFromName(TEXT("Inventory")));
	mStatus = Cast<UButton>(GetWidgetFromName(TEXT("Status")));
	mShop = Cast<UButton>(GetWidgetFromName(TEXT("Shop")));

	mInventory->OnClicked.AddDynamic(this, &USideWidget::InventoryButtonClick);
	mStatus->OnClicked.AddDynamic(this, &USideWidget::StatusButtonClick);
	mShop->OnClicked.AddDynamic(this, &USideWidget::ShopButtonClick);

	UE_LOG(LogUE20251, Warning, TEXT("SideWidget NativeConstruct"));
}

void USideWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void USideWidget::InventoryButtonClick()
{
	UInventoryWidget* Inventory = CUIManager::GetInst()->FindWidget<UInventoryWidget>("Inventory");
	if (Inventory)
	{
		Inventory->OpenUI();
	}
}

void USideWidget::StatusButtonClick()
{
	UE_LOG(LogUE20251, Warning, TEXT("StatusButtonClick"));

	UPlayerStatusWidget* Status = CUIManager::GetInst()->FindWidget<UPlayerStatusWidget>("PlayerStatus");
	if (Status)
	{
		UE_LOG(LogUE20251, Warning, TEXT("OpenUI"));
		Status->OpenUI();
	}
	else
	{
		UE_LOG(LogUE20251, Warning, TEXT("NULL Status"));
	}
}

void USideWidget::ShopButtonClick()
{
	UStoreWidget* Store = CUIManager::GetInst()->FindWidget<UStoreWidget>("Store");
	if (Store)
	{
		Store->OpenUI();
	}
}