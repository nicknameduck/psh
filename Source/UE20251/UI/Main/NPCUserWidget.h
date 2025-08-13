// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "NPCUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UNPCUserWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	UNPCUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mNPCName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProgressBar>	mHPBar;

	// 이 위젯이 보여졌다가 사라질 시간을 계산한다.
	float		mVisibleTime = 3.f;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetNameText(const FString& Name);
	void SetHPPercent(float Percent);
	void EnableHUD();
};
