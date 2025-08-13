// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "StoreItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UStoreItemWidget : public UUserWidget,
	public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UStoreItemWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBorder>	mBack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UImage>	mIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UTextBlock>	mItemName;

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void SetMouseState(EWidgetMouseState State);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
};
