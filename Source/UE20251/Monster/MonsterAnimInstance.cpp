// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "../UEAssetManager.h"
#include "Monster.h"
#include "AIController.h"

void UMonsterAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	FMonsterAnim* Info = UUEAssetManager::Get().FindDataTableRow<FMonsterAnim>(TEXT("DTMonsterAnim"), mAnimKey);

	if (Info)
	{
		mSequenceMap = Info->SequenceMap;
	}
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
	{
		Monster->Attack();
	}
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
	{
		AAIController* AI = Monster->GetController<AAIController>();

		if (IsValid(AI))
		{
			AI->GetBlackboardComponent()->SetValueAsBool(TEXT("AttackEnd"), true);
		}
	}
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
	{
		Monster->OnDissolve();
	}
	//TryGetPawnOwner()->Destroy();
}
