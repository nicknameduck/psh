// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PatrolWait.generated.h"

/**
 * 
 */
UCLASS()
class UE20251_API UBTTask_PatrolWait : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PatrolWait();

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector WaitTime;

	struct FWaitTaskMemory
	{
		FTimerHandle	TimerHandle;
	};

public:
	virtual uint16 GetInstanceMemorySize() const;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);

public:
	void WaitFinish(UBehaviorTreeComponent* OwnerComp);
};
