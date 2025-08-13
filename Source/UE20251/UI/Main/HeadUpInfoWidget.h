// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "HeadUpInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UHeadUpInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHeadUpInfoWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mCharacterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProgressBar>	mHPBar;

protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public:
	void SetNameText(const FString& Name);
	void SetHPPercent(float Percent);
};
