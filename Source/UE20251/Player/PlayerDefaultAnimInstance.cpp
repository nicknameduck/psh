// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDefaultAnimInstance.h"
#include "PlayerCharacter.h"

void UPlayerDefaultAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// 몽타주 재생이 끝날때 호출될 함수를 지정한다.
	OnMontageEnded.AddDynamic(this, &UPlayerDefaultAnimInstance::MontageEnd);

}

void UPlayerDefaultAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerDefaultAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 이 애님인스턴스를 가지고 있는 스켈레탈메시 컴포넌트가 속해있는 Pawn을
	// 얻어오는 기능이다.
	APlayerCharacter* PlayerCharacter =
		Cast<APlayerCharacter>(TryGetPawnOwner());

	// 얻어온 객체가 유효하다면.
	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement =
			PlayerCharacter->GetCharacterMovement();

		if(Movement)
		{
			mMoveSpeed = Movement->Velocity.Size();
			// true일 경우 땅 위에 있다는 것이고 false일 경우 공중에
			// 있다는 것이다.
			mGround = Movement->IsMovingOnGround();
		}
	}
}

void UPlayerDefaultAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerDefaultAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerDefaultAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerDefaultAnimInstance::PlayAttack()
{
	if (!IsValid(mAttackMontage))
		return;

	// 공중에 떠있을 경우
	else if (!mGround)
		return;

	// 공격 중이 아닐 경우 공격중으로 만들어주고 0번 공격을 시작한다.	
	if (!mAttackEnable)
	{
		mAttackEnable = true;

		// 공격 몽타주가 현재 재생중인지 판단한다.
		// 재생중이면 true 아니면 false를 반환한다.
		if (!Montage_IsPlaying(mAttackMontage))
		{
			// 몽타주의 재생 위치를 시작지점으로 되돌려준다.
			Montage_SetPosition(mAttackMontage, 0.f);

			// 몽타주를 재생시킨다.
			Montage_Play(mAttackMontage);

			// 재생할 몽타주 섹션을 지정한다.
			Montage_JumpToSection(mAttackSectionName[0]);
		}
	}

	// 첫번째 공격이 시작되어 공격 중일 경우 Combo가 활성화 되면.
	else if (mAttackCombo)
	{
		// 0, 1, 2, 3    
		mAttackSectionIndex = (mAttackSectionIndex + 1) %
			mAttackSectionName.Num();

		// 몽타주를 재생시킨다.
		Montage_Play(mAttackMontage);

		// 재생할 몽타주 섹션을 지정한다.
		Montage_JumpToSection(mAttackSectionName[mAttackSectionIndex]);

		mAttackCombo = false;
	}
}

void UPlayerDefaultAnimInstance::AnimNotify_JumpTransitionStart()
{
	UE_LOG(LogUE20251, Warning, TEXT("Transition Start"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		TEXT("Transition End"));
}

void UPlayerDefaultAnimInstance::AnimNotify_JumpTransitionEnd()
{
	UE_LOG(LogUE20251, Warning, TEXT("Transition End"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		TEXT("Transition End"));
}

void UPlayerDefaultAnimInstance::AnimNotify_JumpStart()
{
	UE_LOG(LogUE20251, Warning, TEXT("JumpStart"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		TEXT("JumpStart"));
	mJump = false;
}

void UPlayerDefaultAnimInstance::AnimNotify_Attack()
{
}

void UPlayerDefaultAnimInstance::AnimNotify_AttackCombo()
{
	// 콤보공격이 가능하도록 한다.
	mAttackCombo = true;
}

void UPlayerDefaultAnimInstance::MontageEnd(UAnimMontage* Montage, bool Interrupted)
{
	// 공격 몽타주가 끝났을 경우
	if (mAttackMontage == Montage)
	{
		// Interrupted는 정상 종료일 경우 false, 강제로 중단된 경우 true가
		// 들어온다.
		if (!Interrupted)
		{
			mAttackSectionIndex = 0;
			mAttackEnable = false;
			mAttackCombo = false;
		}
	}
}
