// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"
#include "Monster.h"
#include "MonsterMovement.h"

AMonsterController::AMonsterController()
{
	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// 인자로 주소가 아닌 레퍼런스를 받기 때문에 역참조를 통해 객체를 얻어와서
	// 함수의 인자로 전달한다.
	SetPerceptionComponent(*mAIPerception);

	// 감각기관 생성.
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	// 기본 시야 거리. AI가 인식 가능한 최대 거리가 된다.
	mSightConfig->SightRadius = 1000.f;

	// 시야 상실 거리. AI가 대상을 놓치는 거리. SightRadius보다 커야
	// 자연스럽게 처리된다.
	mSightConfig->LoseSightRadius = 1200.f;

	// 시야 각도. 반각이다. 정면 기준으로의 시야 각도를 지정.
	mSightConfig->PeripheralVisionAngleDegrees = 45.f;

	// AI가 마지막으로 본 위치와 가까우면 감지 성공하게 하는 거리.
	mSightConfig->AutoSuccessRangeFromLastSeenLocation = 200.f;

	// 감지 위치를 뒤로 오프셋 하기 위한 값.
	mSightConfig->PointOfViewBackwardOffset = 0.f;

	// AI와 너무 가까운 곳은 감지 안 하도록 필터링.
	mSightConfig->NearClippingRadius = 0.f;

	// 적, 중립, 아군에 대한 감지를 할 것인지 여부를 지정.
	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// 시야를 등록한다.
	mAIPerception->ConfigureSense(*mSightConfig);

	mDamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage"));

	mDamageConfig->Implementation = UAISense_Damage::StaticClass();

	// Damage를 등록한다.
	mAIPerception->ConfigureSense(*mDamageConfig);

	// 주 감각기관을 설정한다.
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());

	SetGenericTeamId(FGenericTeamId(TeamMonster));
}

void AMonsterController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();

	AMonster* Monster = GetPawn<AMonster>();

	if (Monster)
	{
		const FMonsterData& Data = Monster->GetMonsterData();

		mSightConfig->SightRadius = Data.DetectRange;
		mSightConfig->LoseSightRadius = Data.DetectRange + 200.f;
		mSightConfig->PeripheralVisionAngleDegrees = Data.ViewHalfAngle;

		// 시야정보가 갱신되었다면 반드시 다시 재등록 해야 한다.
		mAIPerception->ConfigureSense(*mSightConfig);
	}

	// AI가 감각기관을 이용하여 대상이 감지가 되었을 때 호출될 함수를
	// 지정한다.
	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(this,
		&AMonsterController::OnTarget);
}

void AMonsterController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	// 경로 이동이 성공했을 경우나 중단되었을 경우(Abort) 등등.
	if (Result.Code == EPathFollowingResult::Success)
	{
		// 이 컨트롤러가 빙의된 폰을 얻어온다.
		APawn* ControlPawn = GetPawn();

		if (ControlPawn)
		{
			UMonsterMovement* MoveComp = Cast<UMonsterMovement>(ControlPawn->GetMovementComponent());

			if (MoveComp)
			{
				MoveComp->ClearAIMoveDir();
			}
		}
	}
}

void AMonsterController::StopMovement()
{
	Super::StopMovement();
}

ETeamAttitude::Type AMonsterController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* OtherTeamAgent =
		Cast<const IGenericTeamAgentInterface>(&Other);

	// 이 클래스를 상속받는 객체가 아닐 경우
	if (!OtherTeamAgent)
		return ETeamAttitude::Neutral;

	else if (OtherTeamAgent->GetGenericTeamId().GetId() == TeamNeutral)
		return ETeamAttitude::Neutral;

	return GetGenericTeamId() == OtherTeamAgent->GetGenericTeamId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

void AMonsterController::OnTarget(AActor* Target, FAIStimulus Stimulus)
{
	// 어떤 이벤트가 발생되었는지를 얻어온다.
	TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);

	// 대상이 감지가 되었을 경우.
	if (Stimulus.WasSuccessfullySensed())
	{
		// 인자로 들어온 Target 객체를 현재 AIController가 사용하고 있는
		// Blackboard의 Target Object키에 값을 지정한다.
		Blackboard->SetValueAsObject(TEXT("Target"), Target);
	}

	// 감지된 대상이 제거될 때
	else
	{
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
	}
}

void AMonsterController::OnDamage(AActor* InstigatorActor, float Damage)
{
	//Blackboard->SetValueAsObject(TEXT("Target"), InstigatorActor);
}
