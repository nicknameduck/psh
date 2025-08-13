// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API AWarrior : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AWarrior();

protected:
	virtual void NormalAttack();
};
