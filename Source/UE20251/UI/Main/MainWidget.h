// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UMainWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UMainWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mButtonSample;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget>	mPlayerHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget>	mNPCHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget>	mPlayerStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget>	mStoreWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget>	mInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBaseUserWidget>	mSideMenu;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

protected:
	UFUNCTION()
	void ButtonSampleClick();
};
