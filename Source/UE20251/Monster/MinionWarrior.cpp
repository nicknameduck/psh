// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionWarrior.h"
#include "MonsterController.h"

AMinionWarrior::AMinionWarrior()
{
	mMonsterKey = TEXT("MinionWarrior");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Melee_Dusk.Minion_Lane_Melee_Dusk'"));

	if(MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMeshAsset(MeshAsset.Object);
	}

	mHeadUpWidget->SetRelativeLocation(FVector(0.0, 0.0, 230.0));

	mCapsuleComponent->SetCapsuleHalfHeight(90.f);
	mCapsuleComponent->SetCapsuleRadius(38.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		AIAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/Monster/BTMinion.BTMinion'"));

	if (AIAsset.Succeeded())
		mBehaviorTree = AIAsset.Object;

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABPMinionWarrior.ABPMinionWarrior_C'"));

	if (AnimAsset.Succeeded())
	{
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
	}
}

void AMinionWarrior::BeginPlay()
{
	Super::BeginPlay();
}

void AMinionWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionWarrior::Attack()
{
	AAIController* AI = GetController<AAIController>();

	if (IsValid(AI))
	{
		UBlackboardComponent* BlackboardCom = AI->GetBlackboardComponent();

		if (IsValid(BlackboardCom))
		{
			AActor* Target = Cast<AActor>(BlackboardCom->GetValueAsObject(TEXT("AttackTarget")));

			if (IsValid(Target))
			{
				FDamageEvent	DmgEvent;
				Target->TakeDamage(mMonsterData.Attack, DmgEvent, AI, this);

				//FVector	ImpactLocation = Target
			}
		}
	}
}
