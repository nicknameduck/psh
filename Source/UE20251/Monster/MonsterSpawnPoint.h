// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "../Common/MovePoint.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnPoint.generated.h"

UCLASS()
class UE20251_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterSpawnPoint();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>	mRoot;

#if WITH_EDITORONLY_DATA

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent>	mArrow;

#endif

	// 어떤 클래스로 몬스터를 생성해야 하는지를 지정한다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMonster>	mSpawnClass;

	TObjectPtr<class AMonster>	mSpawnMonster;

	UPROPERTY(EditAnywhere)
	float			mSpawnTime;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem>	mSpawnParticle;

	FTimerHandle	mSpawnTimer;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<AMovePoint>>	mMovePoints;

	UPROPERTY(EditAnywhere)
	float		mPatrolWaitTime = 1.f;

public:
	// 여기서 스폰된 몬스터가 제거될 경우 호출된다.
	void DestroySpawnMonster()
	{
		mSpawnMonster = nullptr;

		if (mSpawnTime > 0.f)
		{
			GetWorldTimerManager().SetTimer(mSpawnTimer, this, &AMonsterSpawnPoint::SpawnTimer, mSpawnTime, false);
		}

		else
		{
			SpawnMonster();
		}
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnTimer();
	void SpawnMonster();
};
