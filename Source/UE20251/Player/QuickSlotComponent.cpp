// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotComponent.h"
#include "../UI/UIManager.h"
#include "../UI/Main/QuickSlotWidget.h"


UQuickSlotComponent::UQuickSlotComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;

	mSlotMaxCount = 10;
}


void UQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	UQuickSlotWidget* QuickSlotWidget = CUIManager::GetInst()->FindWidget<UQuickSlotWidget>(TEXT("QuickSlot"));

	if (QuickSlotWidget)
	{
		QuickSlotWidget->InitQuickSlot(this);
	}
}

void UQuickSlotComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
