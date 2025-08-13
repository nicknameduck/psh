// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PatrolWait.h"
#include "AIController.h"
#include "Monster.h"

UBTTask_PatrolWait::UBTTask_PatrolWait()
{
	NodeName = TEXT("PatrolWait Task");
	bNotifyTick = true;
	bNotifyTaskFinished = true;

	// 블랙보드에서 사용할 키 설정.
	WaitTime.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_PatrolWait, WaitTime));
}

uint16 UBTTask_PatrolWait::GetInstanceMemorySize() const
{
	return sizeof(FWaitTaskMemory);
}

EBTNodeResult::Type UBTTask_PatrolWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 현재 동작되는 AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	// 블랙보드 컴포넌터를 얻어온다.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!AIController || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));

	if (Target)
	{
		return EBTNodeResult::Succeeded;
	}

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	if (!Monster)
	{
		return EBTNodeResult::Failed;
	}

	Monster->ChangeAnimation(EMonsterDefaultAnim::Idle);

	// 노드메모리를 우리가 원하는 타입으로 변경한다.
	FWaitTaskMemory* TaskMemory = (FWaitTaskMemory*)NodeMemory;

	float WaitTimeValue = BlackboardComp->GetValueAsFloat(TEXT("PatrolWaitTime"));

	OwnerComp.GetWorld()->GetTimerManager().SetTimer(TaskMemory->TimerHandle,
		FTimerDelegate::CreateUObject(this, &UBTTask_PatrolWait::WaitFinish,
			&OwnerComp), WaitTimeValue, false);

	return EBTNodeResult::InProgress;
}

void UBTTask_PatrolWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// 현재 동작되는 AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!AIController || !BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));

	if (Target)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_PatrolWait::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	// 현재 동작되는 AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	/*if (Monster)
	{
		Monster->ChangeAnimation(EMonsterDefaultAnim::Idle);
	}*/

	// 노드메모리를 우리가 원하는 타입으로 변경한다.
	FWaitTaskMemory* TaskMemory = (FWaitTaskMemory*)NodeMemory;

	if (TaskMemory->TimerHandle.IsValid())
	{
		OwnerComp.GetWorld()->GetTimerManager().ClearTimer(TaskMemory->TimerHandle);
	}
}

void UBTTask_PatrolWait::WaitFinish(UBehaviorTreeComponent* OwnerComp)
{
	FinishLatentTask(*OwnerComp, EBTNodeResult::Failed);
}
