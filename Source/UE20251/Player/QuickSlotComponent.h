// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlotComponent.h"
#include "QuickSlotComponent.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UQuickSlotComponent : public USlotComponent
{
	GENERATED_BODY()

public:
	UQuickSlotComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
