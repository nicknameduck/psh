// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMonsterDefaultAnim : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Hit,
	Knockback
};


UCLASS()
class UE20251_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName		mAnimKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterDefaultAnim	mAnimType = EMonsterDefaultAnim::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>>	mSequenceMap;

public:
	void SetAnimType(EMonsterDefaultAnim Anim)
	{
		mAnimType = Anim;
	}

public:
	virtual void PostInitProperties() override;
	virtual void NativeBeginPlay();
	virtual void NativeInitializeAnimation();

	// 게임 스레드에서 호출.
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();
};
