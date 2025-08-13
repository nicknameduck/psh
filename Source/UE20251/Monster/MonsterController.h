// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterController();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent>	mAIPerception;

	TObjectPtr<UAISenseConfig_Sight>	mSightConfig;
	TObjectPtr<UAISenseConfig_Damage>	mDamageConfig;

public:
	virtual void OnConstruction(const FTransform& Transform);

protected:
	virtual void BeginPlay() override;

public:
	// 이동이 완료된 후에 호출되는 함수.
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	virtual void StopMovement() override;

public:
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;

public:
	UFUNCTION()
	void OnTarget(AActor* Target, FAIStimulus Stimulus);

	void OnDamage(AActor* InstigatorActor, float Damage);
};
