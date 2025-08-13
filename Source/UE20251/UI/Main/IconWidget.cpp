// Fill out your copyright notice in the Description page of Project Settings.


#include "IconWidget.h"

UIconWidget::UIconWidget(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
}

void UIconWidget::NativeOnInitialized()
{
	Super::NativeConstruct();

	mIcon = Cast<UImage	>(GetWidgetFromName(TEXT("Icon")));
	mCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("Count")));
}

void UIconWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UIconWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UIconWidget::SetIconTexture(UTexture2D* Texture)
{
	mIcon->SetBrushFromTexture(Texture);
}
