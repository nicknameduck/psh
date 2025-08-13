// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "PlayerHUDWidget.generated.h"


UCLASS()
class UE20251_API UPlayerHUDWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UImage>	mPlayerImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mPlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProgressBar>	mHPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProgressBar>	mMPBar;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void SetNameText(const FString& Name);
	void SetHPPercent(float Percent);
	void SetMPPercent(float Percent);
};
