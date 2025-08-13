// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerDefaultAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UPlayerDefaultAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool		mGround = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool		mJump = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mDir = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mAimLookUp = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mAimSide = 0.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage>	mAttackMontage;

	UPROPERTY(EditAnywhere)
	TArray<FName>				mAttackSectionName;

	// 현재 어떤 섹션이 동작하고 있는지 저장할 인덱스.
	int32		mAttackSectionIndex = 0;

	// 공격 중인지 판단한다.
	bool		mAttackEnable = false;

	// 콤보 공격이 가능한지 판단한다.
	bool		mAttackCombo = false;

public:
	void Jump()
	{
		mJump = true;
	}

	void SetDir(float Dir)
	{
		mDir = Dir;
	}

	void SetAimInfo(float LookUp, float Side)
	{
		mAimLookUp = LookUp;
		mAimSide = Side;
	}

public:
	virtual void NativeBeginPlay();
	virtual void NativeInitializeAnimation();

	// 게임 스레드에서 호출.
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	// 애니메이션 스레드에서 호출.
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();

public:
	void PlayAttack();

public:
	// 노티파이를 받을 함수를 만들때 void AnimNotify_이름() 으로 만든다.
	UFUNCTION()
	void AnimNotify_JumpTransitionStart();

	UFUNCTION()
	void AnimNotify_JumpTransitionEnd();

	UFUNCTION()
	void AnimNotify_JumpStart();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackCombo();

	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool Interrupted);
};
