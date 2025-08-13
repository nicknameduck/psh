// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMovement.h"
#include "AIController.h"
#include "Monster.h"

UMonsterMovement::UMonsterMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	mGravityDir = FVector(0.0, 0.0, -1.0);
	mGravity = 980.f;
	mApplyGravity = true;
	mAIMoveDir = FVector::ZeroVector;
	mKnockbackVelocity = FVector::ZeroVector;
}

void UMonsterMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	// AI가 이동하는 기본 이동 방향을 만든다.
	FVector	MoveVelocity = mAIMoveDir * MaxSpeed;


	// 중력을 적용해야 하는 경우
	if (mApplyGravity)
	{
		MoveVelocity += mGravityDir * mGravity;
	}

	// 넉백이 적용되어야 하는 경우. 넉백 방향이 0보다 클 경우
	if (mApplyKnockback)
	{
		// 넉백 벡터를 적용한다.
		MoveVelocity += mKnockbackVelocity;

		mKnockbackVelocity -= mKnockbackInitialVelocity * DeltaTime / mKnockbackDamping;

		// 선형보간 함수를 이용해서 넉백 벡터가 점점 0이 될 수 있게 감소시킨다.
		// 1번인자의 벡터를 2번인자에 들어가는 벡터로 점점 변경한다.
		//mKnockbackVelocity = FMath::VInterpTo(mKnockbackInitialVelocity, FVector::ZeroVector,DeltaTime, mKnockbackDamping);
	}

	// 이동을 처리한다.
	FHitResult	Hit;
	SafeMoveUpdatedComponent(MoveVelocity * DeltaTime, UpdatedComponent->GetComponentRotation(), true, Hit);

	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(MoveVelocity * DeltaTime, 1.f - Hit.Time, Hit.Normal, Hit);
	}

	// 넉백이 적용 상태일 경우
	if (mApplyKnockback)
	{
		bool IsKnockbackHit = false;

		if (Hit.IsValidBlockingHit())
		{
			// 부딪힌 물체가 바닥인지 체크한다.
			bool IsFloorHit = FVector::DotProduct(Hit.Normal, FVector::UpVector) > 0.7f;

			if (!IsFloorHit)
			{
				IsKnockbackHit = true;
			}
		}

		if (IsKnockbackHit || mKnockbackVelocity.SizeSquared() < 1.f)
		{
			UE_LOG(LogUE20251, Warning, TEXT("Knockback End"));
			OnKnockbackEnd();
		}
	}

	Velocity = MoveVelocity;
}

// AIController의 MoveToActor, MoveToLocation 함수가 내부에서 호출해주는 함수로
// UPathFollowingComponent가 FAIMoveRequest를 처리하는 중 목표 위치까지의 직선 방향을 계산해서
// 호출해준다.
void UMonsterMovement::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// AI가 길찾기를 통해 이동할 직선방향을 크기가 1인 단위벡터로 방향만 얻어온다.
	mAIMoveDir = MoveVelocity.GetSafeNormal();
}

void UMonsterMovement::ClearAIMoveDir()
{
	mAIMoveDir = FVector::ZeroVector;
}

void UMonsterMovement::ClearMovement()
{
	mAIMoveDir = FVector::ZeroVector;
	mApplyGravity = false;
	mApplyKnockback = false;
}

void UMonsterMovement::AddKnockbackImpulse(const FVector& Impulse)
{
	mApplyKnockback = true;

	mKnockbackVelocity += Impulse;

	mKnockbackInitialVelocity = mKnockbackVelocity;

	AMonster* Monster = Cast<AMonster>(PawnOwner);

	if (Monster)
	{
		Monster->ChangeAnimation(EMonsterDefaultAnim::Knockback);
	}

	AAIController* AICon = PawnOwner->GetController<AAIController>();

	if (AICon)
	{
		mAIMoveDir = FVector::ZeroVector;
		//AICon->StopMovement();

		if (AICon->BrainComponent)
		{
			//AICon->BrainComponent->PauseLogic(TEXT("Knockback"));
			AICon->BrainComponent->StopLogic(TEXT("Knockback"));
		}
	}
}

void UMonsterMovement::OnKnockbackEnd()
{
	mKnockbackVelocity = FVector::ZeroVector;
	mApplyKnockback = false;

	AMonster* Monster = Cast<AMonster>(PawnOwner);

	if (Monster)
	{
		Monster->ChangeAnimation(EMonsterDefaultAnim::Idle);
	}

	AAIController* AICon = PawnOwner->GetController<AAIController>();

	if (AICon)
	{
		if (AICon->BrainComponent)
		{
			//AICon->BrainComponent->ResumeLogic(TEXT("Knockback End"));
			AICon->BrainComponent->RestartLogic();
		}
	}
}
