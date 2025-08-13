// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "IconWidget.generated.h"


UCLASS()
class UE20251_API UIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UIconWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UImage>	mIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mCount;

	class UBaseUserWidget* mOwnerWidget = nullptr;

	int32		mSlotIndex = 0;

public:
	void SetOwnerWidget(class UBaseUserWidget* OwnerWidget)
	{
		mOwnerWidget = OwnerWidget;
	}

	void SetSlotIndex(int32 Index)
	{
		mSlotIndex = Index;
	}

protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void SetIconTexture(UTexture2D* Texture);
};
