// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "MovePoint.generated.h"

UCLASS()
class UE20251_API AMovePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovePoint();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>	mRoot;

protected:
	virtual void BeginPlay() override;

};
