// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTemplateAnimInstance.h"
#include "PlayerCharacter.h"
#include "../Data/DataSystem.h"

void UPlayerTemplateAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();

	if (!mAnimKey.IsNone())
	{
		const UDataSystem* DataSystem = GetDefault<UDataSystem>();

		if (DataSystem)
		{
			FPlayerAnimInfo* AnimInfo = DataSystem->FindPlayerAnimData(mAnimKey);

			if (AnimInfo)
			{
				mSequenceMap = AnimInfo->SequenceMap;
				mBlendSpaceMap = AnimInfo->BlendSpaceMap;
				mMontageMap = AnimInfo->MontageMap;
				mAttackSectionArray = AnimInfo->AttackSectionArray;
				mAttackMontage = FindAnimMontage(TEXT("Attack"));
			}
		}
	}
}

void UPlayerTemplateAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// 몽타주 재생이 끝날때 호출될 함수를 지정한다.
	OnMontageEnded.AddDynamic(this, &UPlayerTemplateAnimInstance::MontageEnd);
}

void UPlayerTemplateAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerTemplateAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
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

		if (Movement)
		{
			mMoveSpeed = Movement->Velocity.Size();
			// true일 경우 땅 위에 있다는 것이고 false일 경우 공중에
			// 있다는 것이다.
			mGround = Movement->IsMovingOnGround();
		}
	}
}

void UPlayerTemplateAnimInstance::PlayAttack()
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
			Montage_JumpToSection(mAttackSectionArray[0]);
		}
	}

	// 첫번째 공격이 시작되어 공격 중일 경우 Combo가 활성화 되면.
	else if (mAttackCombo)
	{
		// 0, 1, 2, 3    
		mAttackSectionIndex = (mAttackSectionIndex + 1) %
			mAttackSectionArray.Num();

		// 몽타주를 재생시킨다.
		Montage_Play(mAttackMontage);

		// 재생할 몽타주 섹션을 지정한다.
		Montage_JumpToSection(mAttackSectionArray[mAttackSectionIndex]);

		mAttackCombo = false;
	}
}

void UPlayerTemplateAnimInstance::AnimNotify_JumpTransitionStart()
{
	UE_LOG(LogUE20251, Warning, TEXT("Transition Start"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		TEXT("Transition End"));

	UAnimMontage* FallRecovery = FindAnimMontage(TEXT("FallRecovery"));

	if (FallRecovery)
	{
		if (Montage_IsPlaying(FallRecovery))
		{
			Montage_Stop(0.1f, FallRecovery);
		}
	}
}

void UPlayerTemplateAnimInstance::AnimNotify_JumpTransitionEnd()
{
	UE_LOG(LogUE20251, Warning, TEXT("Transition End"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		TEXT("Transition End"));
}

void UPlayerTemplateAnimInstance::AnimNotify_JumpStart()
{
	UE_LOG(LogUE20251, Warning, TEXT("JumpStart"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		TEXT("JumpStart"));
	mJump = false;
	mLandRecoveryAlpha = 0.f;
}

void UPlayerTemplateAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* PlayerCharacter =
		Cast<APlayerCharacter>(TryGetPawnOwner());

	// 얻어온 객체가 유효하다면.
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->NormalAttack();
	}
}

void UPlayerTemplateAnimInstance::AnimNotify_AttackCombo()
{
	// 콤보공격이 가능하도록 한다.
	mAttackCombo = true;
}

void UPlayerTemplateAnimInstance::AnimNotify_LandEnd()
{
	mLandRecoveryAlpha = 1.f;
	UE_LOG(LogUE20251, Warning, TEXT("LandEnd"));

	UAnimMontage* FallRecovery = FindAnimMontage(TEXT("FallRecovery"));

	if (FallRecovery)
	{
		// 몽타주의 재생 위치를 시작지점으로 되돌려준다.
		Montage_SetPosition(FallRecovery, 0.f);

		// 몽타주를 재생시킨다.
		Montage_Play(FallRecovery);
	}
}

void UPlayerTemplateAnimInstance::AnimNotify_LandRecoveryEnd()
{
	mLandRecoveryAlpha = 0.f;
	UE_LOG(LogUE20251, Warning, TEXT("LandRecoveryEnd"));
}

void UPlayerTemplateAnimInstance::AnimNotify_Fall()
{
	UE_LOG(LogUE20251, Warning, TEXT("Fall"));
}

void UPlayerTemplateAnimInstance::MontageEnd(UAnimMontage* Montage, bool Interrupted)
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

UAnimSequence* UPlayerTemplateAnimInstance::FindAnimSequence(const FName& Name)
{
	TObjectPtr<UAnimSequence>* Sequence = mSequenceMap.Find(Name);

	return Sequence->Get();
}

UBlendSpace* UPlayerTemplateAnimInstance::FindBlendSpace(const FName& Name)
{
	TObjectPtr<UBlendSpace>* BlendSpace = mBlendSpaceMap.Find(Name);

	return BlendSpace->Get();
}

UAnimMontage* UPlayerTemplateAnimInstance::FindAnimMontage(const FName& Name)
{
	TObjectPtr<UAnimMontage>* Montage = mMontageMap.Find(Name);

	return Montage->Get();
}
