// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "SelectPawn.generated.h"

UCLASS()
class UE20251_API ASelectPawn : public APawn
{
	GENERATED_BODY()

public:
	ASelectPawn();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent>	mBody;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(EditAnywhere)
	EPlayerJob		mJob;

public:
	EPlayerJob GetPlayerJob()	const
	{
		return mJob;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void EnableOutLine(bool Enable);
};
