// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemViewerWidget.h"

UItemViewerWidget::UItemViewerWidget(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
}

void UItemViewerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	mItemType = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemType")));
	mItemDesc = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDesc")));
	mItemPrice = Cast<UTextBlock>(GetWidgetFromName(TEXT("Price")));
	mItemSell = Cast<UTextBlock>(GetWidgetFromName(TEXT("Sell")));
	mOptionScroll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ItemOptionScroll")));
}

void UItemViewerWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UItemViewerWidget::SetItemInfo(const FItemData& Data)
{
	mItemName->SetText(FText::FromString(Data.ItemName));

	switch (Data.Type)
	{
	case EItemType::Weapon:
		mItemType->SetText(FText::FromString(TEXT("종류 : 무기")));
		break;
	case EItemType::Armor:
		mItemType->SetText(FText::FromString(TEXT("종류 : 방어구")));
		break;
	case EItemType::Etc:
		mItemType->SetText(FText::FromString(TEXT("종류 : 기타")));
		break;
	}

	mItemDesc->SetText(FText::FromString(Data.Desc));

	mItemPrice->SetText(FText::FromString(FString::Printf(TEXT("구매가격 : %d"), Data.Price)));
	mItemSell->SetText(FText::FromString(FString::Printf(TEXT("판매가격 : %d"), Data.Sell)));

	// 기존에 들어가있는 옵션을 모두 지워준다.
	mOptionScroll->ClearChildren();

	// 옵션 수만큼 반복한다.
	for (auto& Option : Data.OptionArray)
	{
		// 텍스트를 출력하기 위한 TextBlock을 생성한다.
		UTextBlock* OptionText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

		//OptionText->Font.Size = 20.f;
		//OptionText->Font.FontObject = 

		// 스크롤 박스에 추가한다.
		mOptionScroll->AddChild(OptionText);

		// OptionText는 스크롤박스에 추가되었기 때문에 slot은 ScrollBoxSlot으로 되어 있다.
		UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(OptionText->Slot);

		ScrollSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		ScrollSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		ScrollSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

		FString	OptionName = GetItemOptionName(Option.Type);

		OptionName += TEXT(" : ") + FString::SanitizeFloat(Option.Option);

		OptionText->SetText(FText::FromString(OptionName));
	}
}
