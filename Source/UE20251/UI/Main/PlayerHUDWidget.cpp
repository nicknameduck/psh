// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

UPlayerHUDWidget::UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("PlayerHUD");
}

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerImage = Cast<UImage>(GetWidgetFromName(TEXT("PlayerImage")));
	mPlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerName")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	mMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));

	//// 버튼 클릭시 호출될 함수를 지정한다.
	//// 호출될 함수는 반환타입 void에 인자가 없는 함수로 UFUNCTION() 으로 지정한다.
	//mButtonSample->OnClicked.AddDynamic(this, &UMainWidget::ButtonSampleClick);
}

void UPlayerHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerHUDWidget::SetNameText(const FString& Name)
{
	mPlayerName->SetText(FText::FromString(Name));
}

void UPlayerHUDWidget::SetHPPercent(float Percent)
{
	mHPBar->SetPercent(Percent);
}

void UPlayerHUDWidget::SetMPPercent(float Percent)
{
	mMPBar->SetPercent(Percent);
}
