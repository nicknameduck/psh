// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadUpInfoWidget.h"


UHeadUpInfoWidget::UHeadUpInfoWidget(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
}

void UHeadUpInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mCharacterName = Cast<UTextBlock>(GetWidgetFromName(TEXT("CharacterName")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	UE_LOG(LogUE20251, Warning, TEXT("HeadUpInfoWidget NativeOnInitialized"));
}

void UHeadUpInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogUE20251, Warning, TEXT("HeadUpInfoWidget Construct"));
}

void UHeadUpInfoWidget::SetNameText(const FString& Name)
{
	mCharacterName->SetText(FText::FromString(Name));
}

void UHeadUpInfoWidget::SetHPPercent(float Percent)
{
	mHPBar->SetPercent(Percent);
}
