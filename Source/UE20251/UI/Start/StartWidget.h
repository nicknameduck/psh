// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UStartWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UStartWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mExitButton;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

protected:
	UFUNCTION()
	void StartClick();

	UFUNCTION()
	void StartHovered();

	UFUNCTION()
	void StartUnHovered();

	UFUNCTION()
	void ExitClick();

	UFUNCTION()
	void ExitHovered();

	UFUNCTION()
	void ExitUnHovered();
};
