// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "SideWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API USideWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
public:
	USideWidget(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>		mInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>		mStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>		mShop;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void InventoryButtonClick();

	UFUNCTION()
	void StatusButtonClick();

	UFUNCTION()
	void ShopButtonClick();
};
