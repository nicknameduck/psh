// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

UMainWidget::UMainWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mButtonSample = Cast<UButton>(GetWidgetFromName(TEXT("ButtonSample")));
	mPlayerHUD = Cast<UBaseUserWidget>(GetWidgetFromName(TEXT("UI_PlayerHUD")));
	mNPCHUD = Cast<UBaseUserWidget>(GetWidgetFromName(TEXT("UI_NPCHUD")));
	mPlayerStatus = Cast<UBaseUserWidget>(GetWidgetFromName(TEXT("UI_PlayerStatus")));
	mStoreWidget = Cast<UBaseUserWidget>(GetWidgetFromName(TEXT("UI_Store_List")));
	mInventory = Cast<UBaseUserWidget>(GetWidgetFromName(TEXT("UI_Inventory")));
	mSideMenu = Cast<UBaseUserWidget>(GetWidgetFromName(TEXT("SideMenu")));

	// 부모 위젯으로 현재 위젯을 지정한다.
	mPlayerHUD->SetParentWidget(this);
	mNPCHUD->SetParentWidget(this);
	mPlayerStatus->SetParentWidget(this);
	mStoreWidget->SetParentWidget(this);
	mInventory->SetParentWidget(this);
	mSideMenu->SetParentWidget(this);
	
	// 버튼 클릭시 호출될 함수를 지정한다.
	// 호출될 함수는 반환타입 void에 인자가 없는 함수로 UFUNCTION() 으로 지정한다.
	mButtonSample->OnClicked.AddDynamic(this, &UMainWidget::ButtonSampleClick);
}

void UMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainWidget::ButtonSampleClick()
{
	UE_LOG(LogUE20251, Warning, TEXT("Button Click"));
}
