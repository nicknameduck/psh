// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Input/Input.h"
#include "PlatformBullet.h"

// Sets default values
APlatformCharacter::APlatformCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mSpringArm->SetupAttachment(GetMesh());

	mCamera->SetupAttachment(mSpringArm);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangAlbino.KwangAlbino'"));

	if(MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -94.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));
	mSpringArm->TargetArmLength = 500.f;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->JumpZVelocity = 550.f;
}

// Called when the game starts or when spawned
void APlatformCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 입력 연결을 위해 PlayerController을 얻어온다.
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// IsValid는 인자로 들어가는 객체가 유효한지 체크한다.
	if (IsValid(PlayerController))
	{
		// EnhancedInput Subsystem을 얻어온다.
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// UPlatformInput 클래스의 CDO를 얻어온다.
		// GetDefault 함수는 <> 안에 들어가는 타입의 CDO를 얻어오는 함수이다. 
		// 이 함수는 const 클래스* 타입을 리턴한다.
		const UPlatformInput* InputCDO = GetDefault<UPlatformInput>();


		// Subsystem에 Context를 등록한다.
		Subsystem->AddMappingContext(InputCDO->mContext, 0);
	}
}

// Called every frame
void APlatformCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 이 함수는 플레이어 컨트롤러에서 여기에 빙의하면서 호출해주는 함수이다.
// UInputComponent 객체는 플레이어 컨트롤러가 가지고 있는 객체이다.
void APlatformCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		const UPlatformInput* InputCDO = GetDefault<UPlatformInput>();

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
			this, &APlatformCharacter::MoveKey);

		EnhancedInput->BindAction(InputCDO->mRotation, ETriggerEvent::Triggered,
			this, &APlatformCharacter::RotationKey);

		EnhancedInput->BindAction(InputCDO->mJump, ETriggerEvent::Started,
			this, &APlatformCharacter::JumpKey);

		EnhancedInput->BindAction(InputCDO->mAttack, ETriggerEvent::Started,
			this, &APlatformCharacter::AttackKey);
	}
}

void APlatformCharacter::MoveKey(const FInputActionValue& Value)
{
	// 인자로 들어온 값을 FVector로 만들어준다.
	// MoveKey는 x, y에 값을 넣어두었다.
	FVector	Dir = Value.Get<FVector>();

	// 1번인자에 들어간 벡터에 2번 인자에 들어간 Scale값을 곱하여 내부에 가지고 있는
	// 벡터에 누적시켜준다.
	AddMovementInput(GetActorForwardVector(), Dir.X);
	AddMovementInput(GetActorRightVector(), Dir.Y);
}

void APlatformCharacter::RotationKey(const FInputActionValue& Value)
{
	float	Angle = Value.Get<float>();

	AddControllerYawInput(Angle);
}

void APlatformCharacter::JumpKey(const FInputActionValue& Value)
{
	// CanJump() 함수는 현재 캐릭터가 점프가 가능한지를 판단해준다.
	if (CanJump())
		Jump();
}

void APlatformCharacter::AttackKey(const FInputActionValue& Value)
{
	FActorSpawnParameters	param;

	/*
	Undefined : 기본설정. 
	AlwaysSpawn	: 충돌을 무시하고 무조건 스폰시킨다.
	AdjustIfPossibleButAlwaysSpawn : 스폰시킬 위치에 부딪히는 물체가 있을 경우 겹쳐지 않는 위치를 찾아보고 있으면 그 위치에 생성하고 없으면 그냥 생성.
	AdjustIfPossibleButDontSpawnIfColliding : 스폰시킬 위치에 부딪히는 물체가 있을 경우 겹쳐지지 않는 위치를 찾아보고 있으면 그 위치에 생성하고 없으면 스폰을 안한다.
	DontSpawnIfColliding : 겹치면 무조건 스폰을 안한다.
	*/
	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector	Location = GetActorLocation() + GetActorForwardVector() * 100.f;

	APlatformBullet* Bullet = GetWorld()->SpawnActor<APlatformBullet>(Location,
		GetActorRotation(), param);
}

