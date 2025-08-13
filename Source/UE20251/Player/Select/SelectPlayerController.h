// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SelectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API ASelectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASelectPlayerController();

protected:
	TObjectPtr<class USelectWidget>	mSelectWidget;
	TObjectPtr<class ASelectPawn>	mHoveredCharacter;
	TObjectPtr<class ASelectPawn>	mPickCharacter;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();

public:
	virtual void Tick(float DeltaTime) override;

public:
	void ClickKey(const FInputActionValue& Value);
};
