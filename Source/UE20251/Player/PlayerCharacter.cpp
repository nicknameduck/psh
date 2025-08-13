// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Input/Input.h"
#include "../UEAssetManager.h"
#include "UEPlayerState.h"
#include "../UI/Main/HeadUpInfoWidget.h"
#include "../UI/Main/PlayerStatusWidget.h"
#include "../UI/Main/PlayerHUDWidget.h"
#include "../UI/UIManager.h"
#include "InventoryComponent.h"
#include "QuickSlotComponent.h"
#include "MainPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureCamera"));
	mHeadUpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadUpInfo"));
	mInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	mQuickSlot = CreateDefaultSubobject<UQuickSlotComponent>(TEXT("QuickSlot"));

	mCaptureCamera->SetupAttachment(GetMesh());

	mSpringArm->SetupAttachment(GetMesh());

	mCamera->SetupAttachment(mSpringArm);

	mHeadUpWidget->SetupAttachment(GetMesh());

	static ConstructorHelpers::FClassFinder<UUserWidget>	HeadUpInfoWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/UI_HeadUpInfo.UI_HeadUpInfo_C'"));

	if (HeadUpInfoWidgetClass.Succeeded())
	{
		mHeadUpWidget->SetWidgetClass(HeadUpInfoWidgetClass.Class);
	}

	mHeadUpWidget->SetWidgetSpace(EWidgetSpace::Screen);
	mHeadUpWidget->SetDrawSize(FVector2D(300.0, 80.0));
	//mHeadUpWidget->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
	mHeadUpWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*static ConstructorHelpers::FObjectFinder<UMaterialInterface>	WidgetMtrl(TEXT("/Script/Engine.Material'/Game/UI/Material/MT_WidgetComponent_World.MT_WidgetComponent_World'"));

	if (WidgetMtrl.Succeeded())
	{
		mHeadUpWidget->SetMaterial(0, WidgetMtrl.Object);
	}*/

	// 위젯컴포넌트의 위치, 회전, 크기 변환을 월드 공간을 기준으로 고정할지 지정하는 기능.
	//mHeadUpWidget->SetAbsolute(false, true, false);

	// 메시는 충돌 금지.
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 캡슐은 플레이어 프로파일을 이용한 충돌처리.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));
	mSpringArm->TargetArmLength = 200.f;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->JumpZVelocity = 550.f;

	SetGenericTeamId(FGenericTeamId(TeamPlayer));

	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>
		HUDCaptureImage(TEXT("/Script/Engine.TextureRenderTarget2D'/Game/RenderTargets/RTPlayerHUD.RTPlayerHUD'"));

	if (HUDCaptureImage.Succeeded())
	{
		mCaptureCamera->TextureTarget = HUDCaptureImage.Object;
	}

	mCaptureCamera->SetRelativeLocation(FVector(0.0, 60.0, 150.0));
	mCaptureCamera->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mCaptureCamera->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	mCaptureCamera->ShowOnlyActors.Add(this);

	mCaptureCamera->CaptureSource = ESceneCaptureSource::SCS_SceneColorHDR;

	mCaptureCamera->ShowFlags.BSP = false;
	mCaptureCamera->ShowFlags.Decals = false;
	mCaptureCamera->ShowFlags.Landscape = false;
	mCaptureCamera->ShowFlags.Translucency = true;
	mCaptureCamera->ShowFlags.SkeletalMeshes = true;
	mCaptureCamera->ShowFlags.StaticMeshes = false;
	mCaptureCamera->ShowFlags.AntiAliasing = true;
	mCaptureCamera->ShowFlags.Atmosphere = false;
	mCaptureCamera->ShowFlags.Cloud = false;
	mCaptureCamera->ShowFlags.Particles = false;
	mCaptureCamera->ShowFlags.Fog = false;

	mCaptureCamera->ShowFlags.InstancedGrass = false;
	mCaptureCamera->ShowFlags.DeferredLighting = true;
	mCaptureCamera->ShowFlags.TextRender = false;
	mCaptureCamera->ShowFlags.InstancedStaticMeshes = false;
	mCaptureCamera->ShowFlags.TemporalAA = false;
	mCaptureCamera->ShowFlags.Paper2DSprites = false;
	mCaptureCamera->ShowFlags.InstancedFoliage = false;

	mCaptureCamera->ShowFlags.EyeAdaptation = true;
	mCaptureCamera->ShowFlags.LocalExposure = true;
	mCaptureCamera->ShowFlags.MotionBlur = false;
	mCaptureCamera->ShowFlags.Bloom = true;
	mCaptureCamera->ShowFlags.ToneCurve = true;
	mCaptureCamera->ShowFlags.Tonemapper = true;
	mCaptureCamera->ShowFlags.PostProcessMaterial = false;

	GetMesh()->bReceivesDecals = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 입력 연결을 위해 PlayerController을 얻어온다.
	AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController());

	// 데이터 테이블로부터 플레이어 정보를 얻어온다.
	FPlayerInfo* Info = UUEAssetManager::Get().FindDataTableRow<FPlayerInfo>(TEXT("DTPlayerInfo"), mDatakey);

	UE_LOG(LogUE20251, Warning, TEXT("APlayerCharacter::BeginPlay"));

	mHeadUpWidgetObject = Cast<UHeadUpInfoWidget>(mHeadUpWidget->GetWidget());

	if (Info)
	{
		AUEPlayerState* State = Cast<AUEPlayerState>(GetPlayerState());

		State->SetPlayerData(*Info);

		State->SetCharacterName(PlayerController->GetPlayerName());

		UPlayerStatusWidget* StatusWidget = CUIManager::GetInst()->FindWidget<UPlayerStatusWidget>(TEXT("PlayerStatus"));

		StatusWidget->SetPlayerData(State->GetPlayerData());

		UPlayerHUDWidget* HUDWidget = CUIManager::GetInst()->FindWidget<UPlayerHUDWidget>(TEXT("PlayerHUD"));

		HUDWidget->SetNameText(State->GetPlayerData().Name);

		mHeadUpWidgetObject->SetNameText(State->GetPlayerData().Name);
		mHeadUpWidgetObject->SetHPPercent(State->GetPlayerData().HP / (float)State->GetPlayerData().HPMax);


	}

	// AnimInstance 객체가 이미 생성된 후에 호출된다.
	// GetAnimInstance() 함수는 UAnimInstance 타입을 반환해준다.
	// 이를 우리가 사용할 타입으로 Cast를 이용하여 형변환해준다.
	mAnimInst = Cast<UPlayerTemplateAnimInstance>(GetMesh()->GetAnimInstance());

	// IsValid는 인자로 들어가는 객체가 유효한지 체크한다.
	if (IsValid(PlayerController))
	{
		// EnhancedInput Subsystem을 얻어온다.
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// UPlatformInput 클래스의 CDO를 얻어온다.
		// GetDefault 함수는 <> 안에 들어가는 타입의 CDO를 얻어오는 함수이다. 
		// 이 함수는 const 클래스* 타입을 리턴한다.
		const UGameInput* InputCDO = GetDefault<UGameInput>();


		// Subsystem에 Context를 등록한다.
		Subsystem->AddMappingContext(InputCDO->mContext, 0);
	}

	if (IsValid(mStatusPictureClass))
	{
		// 월드에 스폰
		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(mStatusPictureClass, FVector(1000000.0, 1000000.0, -1000000.0), FRotator::ZeroRotator, SpawnParam);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 인자로 들어온 Inputcomponent를 EnhancedInputComponent로 형변환한다.
	// EnhancedInputComponent는 InputComponent를 상속받아 만들어져 있고
	// PlayerController는 EnhancedInputComponent로 객체를 생성해서 InputComponent
	// 로 저장해두고 있다.
	UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// 객체가 유효한지 검사한다.
	if (IsValid(EnhancedInput))
	{
		const UGameInput* InputCDO = GetDefault<UGameInput>();

		// Context에 등록된 액션의 키를 눌렀을 경우 혹은 뗐을 경우 동작할 함수를
		// 지정해준다.
		//enum class ETriggerEvent : uint8
		//{
		//	None = (0x0)		UMETA(Hidden), 아무 트리거 이벤트도 발생하지 않음.
		//	Triggered = (1 << 0),	트리거 조건이 충족되었을 때 발생.(누르고 있을때)
		// 일정 임계값을 넘어갔을 경우.
		//	Started = (1 << 1),	입력이 처음 시작될 때.
		//	Ongoing = (1 << 2),	입력이 계속 유지되는 동안 매 프레임 발생.(누르고 있을때)
		//	Canceled = (1 << 3),	입력 도중 중단될때. 입력이 강제로 종료되는 경우.
		//	Completed = (1 << 4),	입력이 끝났을 때.(뗐을 때.)
		//};
		EnhancedInput->BindAction(InputCDO->mMove, ETriggerEvent::Triggered,
			this, &APlayerCharacter::MoveKey);

		EnhancedInput->BindAction(InputCDO->mRotation, ETriggerEvent::Triggered,
			this, &APlayerCharacter::RotationKey);

		EnhancedInput->BindAction(InputCDO->mJump, ETriggerEvent::Started,
			this, &APlayerCharacter::JumpKey);

		EnhancedInput->BindAction(InputCDO->mAttack, ETriggerEvent::Started,
			this, &APlayerCharacter::AttackKey);

		EnhancedInput->BindAction(InputCDO->mCameraRotation, ETriggerEvent::Triggered,
			this, &APlayerCharacter::CameraRotationKey);
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AUEPlayerState* State = Cast<AUEPlayerState>(GetPlayerState());

	Dmg = Dmg - State->GetPlayerData().Defense;

	Dmg = Dmg < 1.f ? 1.f : Dmg;

	State->Damage(Dmg);

	mHeadUpWidgetObject->SetHPPercent(State->GetPlayerData().HP / (float)State->GetPlayerData().HPMax);

	UPlayerStatusWidget* StatusWidget = CUIManager::GetInst()->FindWidget<UPlayerStatusWidget>(TEXT("PlayerStatus"));

	StatusWidget->SetHP(State->GetPlayerData().HP, State->GetPlayerData().HPMax);

	return Dmg;
}


void APlayerCharacter::MoveKey(const FInputActionValue& Value)
{
	// 인자로 들어온 값을 FVector로 만들어준다.
	// MoveKey는 x, y에 값을 넣어두었다.
	FVector	Dir = Value.Get<FVector>();

	// 1번인자에 들어간 벡터에 2번 인자에 들어간 Scale값을 곱하여 내부에 가지고 있는
	// 벡터에 누적시켜준다.
	AddMovementInput(GetActorForwardVector(), Dir.X);
	AddMovementInput(GetActorRightVector(), Dir.Y);

	// 앞, 뒤 둘중 한 방향으로 움직이도록 키를 눌렀을 경우
	if (Dir.X > 0.f)
	{
		mAnimInst->SetDir(0.f);

		if (Dir.Y > 0.f)
			mAnimInst->SetDir(45.f);

		else if (Dir.Y < 0.f)
			mAnimInst->SetDir(-45.f);
	}

	else if (Dir.X < 0.f)
	{
		mAnimInst->SetDir(180.f);

		if (Dir.Y > 0.f)
			mAnimInst->SetDir(135.f);

		else if (Dir.Y < 0.f)
			mAnimInst->SetDir(-135.f);
	}

	else
	{
		if (Dir.Y > 0.f)
			mAnimInst->SetDir(90.f);

		else if (Dir.Y < 0.f)
			mAnimInst->SetDir(-90.f);
	}
}

void APlayerCharacter::RotationKey(const FInputActionValue& Value)
{
	float	Angle = Value.Get<float>();

	AddControllerYawInput(Angle);
}

void APlayerCharacter::JumpKey(const FInputActionValue& Value)
{
	// CanJump() 함수는 현재 캐릭터가 점프가 가능한지를 판단해준다.
	if (CanJump())
	{
		mAnimInst->Jump();
		Jump();
	}
}

void APlayerCharacter::AttackKey(const FInputActionValue& Value)
{
	if (mAnimInst)
		mAnimInst->PlayAttack();
}

void APlayerCharacter::CameraRotationKey(const FInputActionValue& Value)
{
	FVector	Axis = Value.Get<FVector>();

	float	Pitch = Axis.Y * 90.f * GetWorld()->GetDeltaSeconds();
	float	Yaw = Axis.X * 90.f * GetWorld()->GetDeltaSeconds();

	mSpringArm->AddRelativeRotation(FRotator(Pitch, Yaw, 0.0));

	FRotator Rot = mSpringArm->GetRelativeRotation();

	if (Rot.Pitch < -70.0)
		Rot.Pitch = -70.0;

	else if (Rot.Pitch > 70.0)
		Rot.Pitch = 70.0;

	if (Rot.Yaw < -90.0)
		Rot.Yaw += 360.0;

	else if (Rot.Yaw > 270.0)
		Rot.Yaw -= 360.0;

	// LookUp : -90 ~ 270 값을 -180 ~ 180 값을 변경한다.
	mAnimInst->SetAimInfo(Rot.Pitch, Rot.Yaw - 90.0);


	mSpringArm->SetRelativeRotation(Rot);
}

void APlayerCharacter::NormalAttack()
{
}






void APlayerCharacter::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	mTeamID = TeamID;
}

FGenericTeamId APlayerCharacter::GetGenericTeamId()	const
{
	return mTeamID;
}
