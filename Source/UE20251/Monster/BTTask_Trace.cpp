// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Trace.h"
#include "AIController.h"
#include "Monster.h"

UBTTask_Trace::UBTTask_Trace()
{
	NodeName = TEXT("Trace Task");
	bNotifyTick = true;
	bNotifyTaskFinished = true;

	// 블랙보드에서 사용할 키 설정.
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_Trace, TargetKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_Trace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 현재 동작되는 AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	// 블랙보드 컴포넌터를 얻어온다.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (!AIController || !BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));

	if(!Target)
	{
		return EBTNodeResult::Succeeded;
	}

	EPathFollowingRequestResult::Type MoveResult = AIController->MoveToActor(Target);

	// 길찾기에 성공했는지 판단한다.
	if (MoveResult == EPathFollowingRequestResult::Failed)
	{
		return EBTNodeResult::Failed;
	}

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	if(!Monster)
	{
		return EBTNodeResult::Failed;
	}

	Monster->ChangeAnimation(EMonsterDefaultAnim::Run);

	UE_LOG(LogUE20251, Warning, TEXT("Trace Execute"));

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Trace::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController)
	{
		AIController->StopMovement();
	}

	return EBTNodeResult::Aborted;
}

void UBTTask_Trace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// 현재 동작되는 AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return;

	// 블랙보드에 지정된 타겟이 없어질 경우 태스크 종료.
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetKey.SelectedKeyName));

	if (!Target)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	if (!Monster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	EPathFollowingStatus::Type PathStatus = AIController->GetMoveStatus();

	// 도착인지 실패인지 판단한다.
	if (PathStatus == EPathFollowingStatus::Idle)
	{
		UE_LOG(LogUE20251, Warning, TEXT("PathFollowing Idle"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// 타겟의 위치로 이동시킨다.
	float AttackRange = BlackboardComp->GetValueAsFloat(TEXT("AttackRange"));

	FVector	TargetLocation, MonsterLocation;

	// 타겟의 위치를 얻어온다. 단, 발밑 가운데를 기준으로 위치를 지정할 것이기 때문에 캡슐의
	// 절반 높이만큼을 아래로 내린 위치를 구한다.
	TargetLocation = Target->GetActorLocation();

	// 루트컴포넌트가 캡슐일 경우 절반 높이만큼을 아래로 내려준다.
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (Capsule)
	{
		TargetLocation.Z -= Capsule->GetScaledCapsuleHalfHeight();
	}

	// 몬스터 위치를 구한다.
	MonsterLocation = Monster->GetActorLocation();

	Capsule = Cast<UCapsuleComponent>(Monster->GetRootComponent());

	// 몬스터는 루트컴포넌트가 무조건 Capsule로 정해져 있다.
	MonsterLocation.Z -= Capsule->GetScaledCapsuleHalfHeight();

	// 둘 사이의 거리를 구한다.
	float Distance = FVector::Dist(TargetLocation, MonsterLocation);

	// 둘 사이의 거리가 공격할 거리보다 가까울 경우 공격 반경 안에 도착한 것으로 판단한다.
	if (Distance <= AttackRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}

void UBTTask_Trace::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	// 현재 동작되는 AIController를 얻어온다.
	AAIController* AIController = OwnerComp.GetAIOwner();

	AIController->StopMovement();

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	/*if (Monster)
	{
		Monster->ChangeAnimation(EMonsterDefaultAnim::Idle);
	}*/

	/*if (TaskResult == EBTNodeResult::Succeeded)
	{
		UE_LOG(LogUE20251, Warning, TEXT("Trace Succeeded"));
	}

	else if (TaskResult == EBTNodeResult::Failed)
	{
		UE_LOG(LogUE20251, Warning, TEXT("Trace Failed"));
	}

	else if(TaskResult == EBTNodeResult::Aborted)
	{
		UE_LOG(LogUE20251, Warning, TEXT("Trace Aborted"));
	}*/
}
