// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCUserWidget.h"

UNPCUserWidget::UNPCUserWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
}

void UNPCUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNPCName = Cast<UTextBlock>(GetWidgetFromName(TEXT("NPCName")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}

void UNPCUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UNPCUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 현재 위젯이 보여지고 있을 경우
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		// 보여질 시간을 감소시켜준다.
		mVisibleTime -= InDeltaTime;

		if (mVisibleTime <= 0.f)
		{
			mVisibleTime = 0.f;
			// 위젯을 안보이게 한다.
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UNPCUserWidget::SetNameText(const FString& Name)
{
	mNPCName->SetText(FText::FromString(Name));
}

void UNPCUserWidget::SetHPPercent(float Percent)
{
	mHPBar->SetPercent(Percent);
}

void UNPCUserWidget::EnableHUD()
{
	SetVisibility(ESlateVisibility::Visible);

	mVisibleTime = 3.f;
}
