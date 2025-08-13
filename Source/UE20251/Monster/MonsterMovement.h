// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MonsterMovement.generated.h"


UCLASS()
class UE20251_API UMonsterMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
public:
	UMonsterMovement();

protected:
	// 중력을 적용 할지
	bool	mApplyGravity = true;

	// 중력 값.
	float	mGravity = 980.f;

	// 중력이 적용될 방향.
	FVector	mGravityDir;

	// AI의 이동 방향을 저장할 벡터.
	FVector	mAIMoveDir;

	bool	mApplyKnockback = false;

	// 넉백이 동작할 방향.
	FVector	mKnockbackVelocity;
	FVector	mKnockbackInitialVelocity;

	// 넉백이 얼마나 빨리 적용될지.
	float	mKnockbackDamping = 2.f;


public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	void ClearAIMoveDir();
	void ClearMovement();

	void EnableGravity(bool Enable)
	{
		mApplyGravity = Enable;
	}

	void AddKnockbackImpulse(const FVector& Impulse);
	void SetKnockbackDamping(float Damping)
	{
		mKnockbackDamping = Damping;
	}


private:
	void OnKnockbackEnd();
};
