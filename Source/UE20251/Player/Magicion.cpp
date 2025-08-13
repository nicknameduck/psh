// Fill out your copyright notice in the Description page of Project Settings.


#include "Magicion.h"
#include "UEPlayerState.h"
#include "Magician/MagicianNormalAttack.h"

AMagicion::AMagicion()
{
	mDatakey = TEXT("Magician");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);

	mHeadUpWidget->SetRelativeLocation(FVector(0.0, 0.0, 190.0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	// 클래스 정보를 읽어올 경우 경로의 가장 끝에 _C를 무조건 붙여야 한다.
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/Magicion/ABPMagicion.ABPMagicion_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	static ConstructorHelpers::FClassFinder<AActor>
		StatusPictureClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BPStatusPicture_Magician.BPStatusPicture_Magician_C'"));

	if (StatusPictureClass.Succeeded())
		mStatusPictureClass = StatusPictureClass.Class;
}

void AMagicion::NormalAttack()
{
	FName	AttackSocketName;

	if (mAnimInst->GetAttackSectionIndex() % 2 == 0)
	{
		AttackSocketName = TEXT("Attack_r");
	}

	else
	{
		AttackSocketName = TEXT("Attack_l");
	}

	AUEPlayerState* State = GetPlayerState<AUEPlayerState>();

	const FPlayerData& Data = State->GetPlayerData();

	FVector	AttackPos = GetMesh()->GetSocketLocation(AttackSocketName);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMagicianNormalAttack* Attack = GetWorld()->SpawnActor<AMagicianNormalAttack>(AttackPos, GetActorRotation(), param);

	Attack->SetDamage(Data.Attack);
	Attack->SetOwnerController(GetController());
}
