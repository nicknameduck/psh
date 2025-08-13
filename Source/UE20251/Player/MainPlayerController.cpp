// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//FInputModeGameOnly
	//FInputModeUIOnly
	//FInputModeGameAndUI
	FInputModeGameAndUI	MainInputMode;

	SetInputMode(MainInputMode);

	// 클라이언트일 경우
	if (IsLocalController())
	{
		mMainWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/UI_Main.UI_Main_C'"));

		if (IsValid(mMainWidgetClass))
		{
			UUserWidget* MainWidget = CreateWidget<UUserWidget>(this,
				mMainWidgetClass);

			if (MainWidget)
			{
				MainWidget->AddToViewport();
			}
		}
	}
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
