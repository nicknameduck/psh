// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "SelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API USelectWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	USelectWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UButton>	mStartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UEditableTextBox>	mInputName;

	EPlayerJob		mSelectJob;

public:
	void SetSelectJob(EPlayerJob Job)
	{
		mSelectJob = Job;
	}

protected:
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void EnableStartButton(bool Enable);

protected:
	UFUNCTION()
	void StartClick();

	UFUNCTION()
	void TextCommit(const FText& Text, ETextCommit::Type CommitMethod);
};
