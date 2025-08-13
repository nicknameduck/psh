// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "MinionWarrior.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API AMinionWarrior : public AMonster
{
	GENERATED_BODY()

public:
	AMinionWarrior();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Attack();
};
