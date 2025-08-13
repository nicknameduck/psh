// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreItemWidget.h"
#include "ItemDataObject.h"

UStoreItemWidget::UStoreItemWidget(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
}

void UStoreItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mBack = Cast<UBorder>(GetWidgetFromName(TEXT("Back")));
	mIcon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	mItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}

void UStoreItemWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStoreItemWidget::SetMouseState(EWidgetMouseState State)
{
	switch (State)
	{
	case EWidgetMouseState::None:
		mBack->SetContentColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		mBack->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
		break;
	case EWidgetMouseState::Hovered:
		mBack->SetContentColorAndOpacity(FLinearColor(1.f, 1.f, 0.f, 1.f));
		mBack->SetBrushColor(FLinearColor(1.f, 1.f, 0.f, 1.f));
		break;
	case EWidgetMouseState::Select:
		mBack->SetContentColorAndOpacity(FLinearColor(1.f, 0.f, 0.f, 1.f));
		mBack->SetBrushColor(FLinearColor(1.f, 0.f, 0.f, 1.f));
		break;
	}
}

void UStoreItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UItemDataObject* Data = Cast<UItemDataObject>(ListItemObject);

	if (Data)
	{
		mIcon->SetBrushFromTexture(Data->GetItemData().Icon);
		mItemName->SetText(FText::FromString(Data->GetItemData().ItemName));

		SetMouseState(Data->GetItemState());
	}
}
