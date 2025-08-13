// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionRanger.h"

AMinionRanger::AMinionRanger()
{
	mMonsterKey = TEXT("MinionRanger");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Ranged_Dusk.Minion_Lane_Ranged_Dusk'"));

	if (MeshAsset.Succeeded())
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
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABPMinionRanger.ABPMinionRanger_C'"));

	if (AnimAsset.Succeeded())
	{
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
	}
}

void AMinionRanger::BeginPlay()
{
	Super::BeginPlay();

}

void AMinionRanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionRanger::Attack()
{
}
