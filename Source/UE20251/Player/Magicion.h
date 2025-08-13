// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Magicion.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API AMagicion : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AMagicion();

protected:
	virtual void NormalAttack();
};
