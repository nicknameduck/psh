// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../UEAssetManager.h"
#include "MonsterController.h"
#include "MonsterMovement.h"
#include "MonsterSpawnPoint.h"
#include "../UI/UIManager.h"
#include "../UI/Main/NPCUserWidget.h"
#include "../UI/Main/HeadUpInfoWidget.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	mCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mHeadUpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadUpInfo"));
	mMovement = CreateDefaultSubobject<UMonsterMovement>(TEXT("Movement"));

	mCapsuleComponent->SetCanEverAffectNavigation(false);
	mMesh->SetCanEverAffectNavigation(false);

	SetRootComponent(mCapsuleComponent);

	mCapsuleComponent->bVisualizeComponent = true;

	mMesh->SetupAttachment(mCapsuleComponent);

	mHeadUpWidget->SetupAttachment(mMesh);

	static ConstructorHelpers::FClassFinder<UUserWidget>	HeadUpInfoWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/UI_HeadUpInfo.UI_HeadUpInfo_C'"));

	if (HeadUpInfoWidgetClass.Succeeded())
	{
		mHeadUpWidget->SetWidgetClass(HeadUpInfoWidgetClass.Class);
	}

	mHeadUpWidget->SetWidgetSpace(EWidgetSpace::World);
	mHeadUpWidget->SetDrawSize(FVector2D(300.0, 80.0));
	mHeadUpWidget->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
	mHeadUpWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>	WidgetMtrl(TEXT("/Script/Engine.Material'/Game/UI/Material/MT_WidgetComponent_World.MT_WidgetComponent_World'"));

	if (WidgetMtrl.Succeeded())
	{
		mHeadUpWidget->SetMaterial(0, WidgetMtrl.Object);
	}
	
	// 위젯컴포넌트의 위치, 회전, 크기 변환을 월드 공간을 기준으로 고정할지 지정하는 기능.
	mHeadUpWidget->SetAbsolute(false, true, false);

	mCapsuleComponent->SetCollisionProfileName(TEXT("Monster"));

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterController::StaticClass();


	// MovementComponent가 업데이트할 컴포넌트를 지정한다.
	mMovement->SetUpdatedComponent(RootComponent);

	bUseControllerRotationYaw = true;

	SetGenericTeamId(FGenericTeamId(TeamMonster));

	mMesh->bReceivesDecals = false;

	//mMesh->bRenderCustomDepth = true;
}

void AMonster::ChangeAnimation(EMonsterDefaultAnim Anim)
{
	if (Anim == EMonsterDefaultAnim::Walk)
	{
		mMovement->MaxSpeed = mMonsterData.MoveSpeed * 0.5f;
	}

	else if (Anim == EMonsterDefaultAnim::Run)
	{
		mMovement->MaxSpeed = mMonsterData.MoveSpeed;
	}

	else if (Anim == EMonsterDefaultAnim::Idle)
	{
		UE_LOG(LogUE20251, Warning, TEXT("Idle"));
	}

	if (mAnimInst)
		mAnimInst->SetAnimType(Anim);
}

void AMonster::SetMovePoints(const TArray<TObjectPtr<AMovePoint>>& MovePoints)
{
	mMovePoints = MovePoints;

	if (mMovePoints.IsEmpty())
		return;

	mPatrolPoints.Empty();

	// 스폰포인트의 위치를 넣어준다.
	if (mSpawnPoint)
	{
		mPatrolPoints.Add(mSpawnPoint->GetActorLocation());
	}

	// 이동해야 할 포인트들의 위치를 넣어준다.
	for (auto& Point : mMovePoints)
	{
		mPatrolPoints.Add(Point->GetActorLocation());
	}
}

void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FMonsterInfo* Info = UUEAssetManager::Get().FindDataTableRow<FMonsterInfo>(TEXT("DTMonsterInfo"), mMonsterKey);

	if (Info)
	{
		mMonsterData.Name = Info->Name;
		mMonsterData.Attack = Info->Attack;
		mMonsterData.Defense = Info->Defense;
		mMonsterData.HP = Info->HP;
		mMonsterData.HPMax = Info->HP;
		mMonsterData.MP = Info->MP;
		mMonsterData.MPMax = Info->MP;
		mMonsterData.AttackSpeed = Info->AttackSpeed;
		mMonsterData.MoveSpeed = Info->MoveSpeed;
		mMonsterData.AttackRange = Info->AttackRange;
		mMonsterData.DetectRange = Info->DetectRange;
		mMonsterData.ViewHalfAngle = Info->ViewHalfAngle;
		mMonsterData.Level = Info->Level;
		mMonsterData.Exp = Info->Exp;
		mMonsterData.Gold = Info->Gold;

		mMovement->MaxSpeed = mMonsterData.MoveSpeed;
	}
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	mAnimInst = Cast<UMonsterAnimInstance>(mMesh->GetAnimInstance());

	FMonsterInfo* Info = UUEAssetManager::Get().FindDataTableRow<FMonsterInfo>(TEXT("DTMonsterInfo"), mMonsterKey);

	UE_LOG(LogUE20251, Warning, TEXT("AMonster::BeginPlay"));

	mHeadUpWidgetObject = Cast<UHeadUpInfoWidget>(mHeadUpWidget->GetWidget());

	if (Info)
	{
		mMonsterData.Name = Info->Name;
		mMonsterData.Attack = Info->Attack;
		mMonsterData.Defense = Info->Defense;
		mMonsterData.HP = Info->HP;
		mMonsterData.HPMax = Info->HP;
		mMonsterData.MP = Info->MP;
		mMonsterData.MPMax = Info->MP;
		mMonsterData.AttackSpeed = Info->AttackSpeed;
		mMonsterData.MoveSpeed = Info->MoveSpeed;
		mMonsterData.AttackRange = Info->AttackRange;
		mMonsterData.DetectRange = Info->DetectRange;
		mMonsterData.ViewHalfAngle = Info->ViewHalfAngle;
		mMonsterData.Level = Info->Level;
		mMonsterData.Exp = Info->Exp;
		mMonsterData.Gold = Info->Gold;

		mMovement->MaxSpeed = mMonsterData.MoveSpeed;

		mHeadUpWidgetObject->SetNameText(mMonsterData.Name);
		mHeadUpWidgetObject->SetHPPercent(mMonsterData.HP / (float)mMonsterData.HPMax);
	}

	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController && mBehaviorTree)
	{
		AIController->RunBehaviorTree(mBehaviorTree);

		AIController->GetBlackboardComponent()->SetValueAsFloat(TEXT("DetectRange"), mMonsterData.DetectRange);
		AIController->GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), mMonsterData.AttackRange);
	}

	else
	{
		UE_LOG(LogUE20251, Warning, TEXT("MinionWarrior: Failed to run behavior tree."));
	}

	// Material을 DynamicMaterialInstance로 만들어준다.
	int32	MtrlCount = mMesh->GetNumMaterials();

	for (int32 i = 0; i < MtrlCount; ++i)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		Mtrl->BlendMode = EBlendMode::BLEND_Masked;

		mMaterials.Add(Mtrl);
	}
}

/*
Destroyed : 액터가 제거될 때(Destroy 함수 호출 시)
LevelTransition : 다른 레벨로 전환되며 액터가 언로드 상황일 경우
EndPlayInEditor : 에디터 모드에서 플레이를 중지할 때
RemovedFromWorld : 액터가 월드에서 제거될 때, 서브 레벨 언로드 또는 액터 제거시
Quit : 게임 종료될 때
*/
void AMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	switch (EndPlayReason)
	{
	case EEndPlayReason::Destroyed:
		if (mSpawnPoint)
		{
			mSpawnPoint->DestroySpawnMonster();
		}
		break;
	case EEndPlayReason::LevelTransition:
		break;
	case EEndPlayReason::EndPlayInEditor:
		break;
	case EEndPlayReason::RemovedFromWorld:
		break;
	case EEndPlayReason::Quit:
		break;
	}
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mDissolveEnable)
	{
		mDissolve -= 1.5f * DeltaTime / mDissolveTime;

		if (mDissolve <= -1.f)
		{
			Destroy();
		}

		for (auto& Mtrl : mMaterials)
		{
			Mtrl->SetScalarParameterValue(TEXT("Dissolve"), mDissolve);
		}
	}

	if (mHitEnable)
	{
		mHitAccTime += DeltaTime;

		if (mHitAccTime >= mHitTime)
		{
			mHitEnable = false;
			mHitAccTime = 0.f;

			for (auto& Mtrl : mMaterials)
			{
				Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 0.f);
			}
		}
	}
}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float Damage = DamageAmount - mMonsterData.Defense;
	Damage = Damage < 1 ? 1 : Damage;

	AMonsterController* MonsterController = Cast<AMonsterController>(GetController());

	mMonsterData.HP -= Damage;

	// 다른 AI가 이 액터의 데미지를 감지할 수 있도록 한다.
	UAISense_Damage::ReportDamageEvent(GetWorld(), MonsterController, DamageCauser, Damage, DamageCauser->GetActorLocation(), GetActorLocation());

	MonsterController->OnDamage(DamageCauser, Damage);

	if (mMonsterData.HP <= 0.f)
	{
		mMonsterData.HP = 0.f;

		//Destroy();
		
		// 이동을 멈춘다.
		MonsterController->StopMovement();
		// AI 동작을 멈춘다.
		MonsterController->BrainComponent->StopLogic(TEXT("Death"));

		mCapsuleComponent->SetCollisionProfileName(TEXT("MonsterDeath"));

		mMovement->ClearMovement();

		ChangeAnimation(EMonsterDefaultAnim::Death);

		DamageAmount = -1.f;
	}

	// 데미지를 받았는데 살아있을 경우 Hit 활성화
	else
	{
		OnHit();
	}

	UNPCUserWidget* NPCHUD = CUIManager::GetInst()->FindWidget<UNPCUserWidget>(TEXT("NPCHUD"));

	if (NPCHUD)
	{
		NPCHUD->SetNameText(mMonsterData.Name);
		NPCHUD->SetHPPercent(mMonsterData.HP / (float)mMonsterData.HPMax);
		NPCHUD->EnableHUD();
	}

	mHeadUpWidgetObject->SetHPPercent(mMonsterData.HP / (float)mMonsterData.HPMax);

	return DamageAmount;
}

void AMonster::Attack()
{
}






void AMonster::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	mTeamID = TeamID;
}

FGenericTeamId AMonster::GetGenericTeamId()	const
{
	return mTeamID;
}
