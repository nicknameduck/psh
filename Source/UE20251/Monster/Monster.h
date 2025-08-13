// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "../Common/MovePoint.h"
#include "MonsterAnimInstance.h"
#include "MonsterMovement.h"
#include "GameFramework/Pawn.h"
#include "Monster.generated.h"

UCLASS()
class UE20251_API AMonster : public APawn,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> mCapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent>		mHeadUpWidget;

	TObjectPtr<class UHeadUpInfoWidget>	mHeadUpWidgetObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMonsterMovement>	mMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FMonsterData mMonsterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FName	mMonsterKey;

	UBehaviorTree* mBehaviorTree;

	TObjectPtr<class UMonsterAnimInstance> mAnimInst;

	class AMonsterSpawnPoint* mSpawnPoint = nullptr;

	// 월드에 배치되어 있는 이동 액터들.
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<AMovePoint>>	mMovePoints;

	// 자신이 생성된 위치와 월드에 배치되어 있는 액터들을 위치로 받아놓은 배열.
	// 실제 이 값을 이용해서 이동한다.
	UPROPERTY(VisibleAnywhere)
	TArray<FVector>		mPatrolPoints;

	// PatrolPoints 배열에서 어떤 포인트로 이동해야 하는지에 대한 인덱스를 저장한다.
	// 1로 해놓은 이유는 0번은 시작위치이기 때문이다.
	int32		mPatrolIndex = 1;

	FGenericTeamId	mTeamID;

	TArray<TObjectPtr<UMaterialInstanceDynamic>>	mMaterials;

	bool			mDissolveEnable = false;
	float			mDissolve = 0.5f;
	float			mDissolveTime = 3.f;

	bool			mHitEnable = false;
	float			mHitTime = 0.2f;
	float			mHitAccTime = 0.f;

public:
	const FMonsterData& GetMonsterData() const
	{
		return mMonsterData;
	}

	UMonsterMovement* GetMonsterMovement()	const
	{
		return mMovement;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

	bool IsPatrol()	const
	{
		return !mPatrolPoints.IsEmpty();
	}

	const FVector& GetPatrolPoint()	const
	{
		return mPatrolPoints[mPatrolIndex];
	}

	void NextPatrolPoint()
	{
		mPatrolIndex = (mPatrolIndex + 1) % mPatrolPoints.Num();
	}

	void ChangeAnimation(EMonsterDefaultAnim Anim);
	void SetMovePoints(const TArray<TObjectPtr<AMovePoint>>& MovePoints);

public:
	virtual void OnConstruction(const FTransform& Transform);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	virtual void Attack();


public:
	void OnDissolve()
	{
		mDissolveEnable = true;

		// Dissolve를 켜준다.
		for (auto& Mtrl : mMaterials)
		{
			Mtrl->SetScalarParameterValue(TEXT("DissolveEnable"), 1.f);
		}

		mMesh->SetSimulatePhysics(true);
	}

	void OnHit()
	{
		mHitEnable = true;
		mHitAccTime = 0.f;

		for (auto& Mtrl : mMaterials)
		{
			Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 1.f);
		}
	}



public:
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId()	const;
};
