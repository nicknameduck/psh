// Fill out your copyright notice in the Description page of Project Settings.


#include "StartWidget.h"

UStartWidget::UStartWidget(const FObjectInitializer& ObjectInitializer)	:
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("Start");
}


void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

	mStartButton->OnClicked.AddDynamic(this, &UStartWidget::StartClick);
	mStartButton->OnHovered.AddDynamic(this, &UStartWidget::StartHovered);
	mStartButton->OnUnhovered.AddDynamic(this, &UStartWidget::StartUnHovered);

	mExitButton->OnClicked.AddDynamic(this, &UStartWidget::ExitClick);
	mExitButton->OnHovered.AddDynamic(this, &UStartWidget::ExitHovered);
	mExitButton->OnUnhovered.AddDynamic(this, &UStartWidget::ExitUnHovered);
}

void UStartWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStartWidget::StartClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("CharacterSelect"));
}

void UStartWidget::StartHovered()
{
	PlayWidgetAnimation(TEXT("StartButtonHovered"));
}

void UStartWidget::StartUnHovered()
{
	PlayWidgetAnimation(TEXT("StartButtonHovered"), 0.f, 1.f, false);
}

void UStartWidget::ExitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UStartWidget::ExitHovered()
{
	PlayWidgetAnimation(TEXT("ExitButtonHovered"));
}

void UStartWidget::ExitUnHovered()
{
	PlayWidgetAnimation(TEXT("ExitButtonHovered"), 0.f, 1.f, false);
}
