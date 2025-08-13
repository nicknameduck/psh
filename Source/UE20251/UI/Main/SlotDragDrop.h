// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../BaseUserWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDrop.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API USlotDragDrop : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	// 이전 슬롯 인덱스를 저장한다.
	int32	mPrevSlotIndex = -1;

	// 이전에 어떤 창에 있던 슬롯인지 저장한다.
	UBaseUserWidget* mPrevWidget = nullptr;

	// 이전에 어떤 컴포넌트에 속한 슬롯인지 저장한다.
	class USlotComponent* mPrevSlotComponent = nullptr;
};
