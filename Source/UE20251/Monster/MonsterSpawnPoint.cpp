// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "Monster.h"
#include "AIController.h"

AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;

#if WITH_EDITORONLY_DATA

	mArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	mArrow->ArrowColor = FColor(255, 0, 0);
	mArrow->bTreatAsASprite = true;
	mArrow->bIsScreenSizeScaled = true;
	mArrow->SetSimulatePhysics(false);
	
	mArrow->SetupAttachment(mRoot);

#endif

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		SpawnAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Shared/P_MinionSpawn.P_MinionSpawn'"));

	if (SpawnAsset.Succeeded())
	{
		mSpawnParticle = SpawnAsset.Object;
	}

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnMonster();
}

void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawnPoint::SpawnTimer()
{
	GetWorldTimerManager().ClearTimer(mSpawnTimer);

	SpawnMonster();
}

void AMonsterSpawnPoint::SpawnMonster()
{
	// 생성할 몬스터 클래스가 없을 경우
	if (!IsValid(mSpawnClass))
		return;

	// 스폰시 재생할 파티클이 있을 경우
	if (IsValid(mSpawnParticle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mSpawnParticle,
			GetActorLocation());
	}

	// 몬스터를 스폰시킨다.
	FActorSpawnParameters	Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector	SpawnLocation = GetActorLocation();

	// Monster CDO를 얻어온다.
	AMonster* MonsterCDO = mSpawnClass->GetDefaultObject<AMonster>();

	if (IsValid(MonsterCDO))
	{
		UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(MonsterCDO->GetRootComponent());

		// 생성할 위치를 바닥에서 캡슐의 절반 높이만큼 위로 올려준 위치로 지정한다.
		SpawnLocation.Z += Capsule->GetScaledCapsuleHalfHeight();
	}

	mSpawnMonster = GetWorld()->SpawnActor<AMonster>(mSpawnClass, SpawnLocation,
		GetActorRotation(), Param);

	// 몬스터가 생성된 스폰포인트를 가지고 있을 수 있게 지정해준다.
	mSpawnMonster->SetSpawnPoint(this);

	// 이동 경로를 넘겨준다.
	mSpawnMonster->SetMovePoints(mMovePoints);

	AAIController* AI = mSpawnMonster->GetController<AAIController>();

	if (AI)
	{
		AI->GetBlackboardComponent()->SetValueAsFloat(TEXT("PatrolWaitTime"), mPatrolWaitTime);
	}
}

