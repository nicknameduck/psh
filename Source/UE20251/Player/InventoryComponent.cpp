// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../UI/Main/ItemDataObject.h"
#include "../UI/UIManager.h"
#include "../UI/Main/InventoryWidget.h"
#include "../UEAssetManager.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	UInventoryWidget* InventoryWidget = CUIManager::GetInst()->FindWidget<UInventoryWidget>(TEXT("Inventory"));

	if (InventoryWidget)
	{
		InventoryWidget->InitInventory(this);
	}
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


bool UInventoryComponent::AddItem(const FName& ItemName)
{
	// 인벤토리가 꽉 찼을 경우
	if (IsFull())
	{
		return false;
	}

	FItemTableInfo* Info = UUEAssetManager::Get().FindDataTableRow<FItemTableInfo>(TEXT("DTItemInfo"), ItemName);

	return AddItem(Info);
}

bool UInventoryComponent::AddItem(FItemTableInfo* Info)
{
	// 인벤토리가 꽉 찼을 경우
	if (IsFull() || !Info)
	{
		return false;
	}

	UItemDataObject* ItemObj = NewObject<UItemDataObject>();

	ItemObj->SetItemData(Info);

	AddSlot(Cast<USlotData>(ItemObj));

	return true;
}

bool UInventoryComponent::AddItem(const FItemData& Info)
{
	// 인벤토리가 꽉 찼을 경우
	if (IsFull())
	{
		return false;
	}

	UItemDataObject* ItemObj = NewObject<UItemDataObject>();

	ItemObj->SetItemData(Info);

	AddSlot(Cast<USlotData>(ItemObj));

	return true;
}

void UInventoryComponent::SetGold(int32 Gold)
{
}
