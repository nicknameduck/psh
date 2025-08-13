// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlotComponent.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE20251_API UInventoryComponent : public USlotComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool AddItem(const FName& ItemName);
	bool AddItem(FItemTableInfo* Info);
	bool AddItem(const FItemData& Info);
	void SetGold(int32 Gold);
};
