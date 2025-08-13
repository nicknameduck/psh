// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerController.h"
#include "../../Input/Input.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SelectPawn.h"
#include "../../UI/Select/SelectWidget.h"

ASelectPlayerController::ASelectPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	SetShowMouseCursor(true);
}

void ASelectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	Mode;

	SetInputMode(Mode);

	// 선택용 위젯 생성.
	// 생성할 위젯 클래스를 로딩한다. 생성자가 아닌 곳에서는 LoadClass를 이용해서 클래스 정보를 불러올 수 있다.
	TSubclassOf<USelectWidget>	WidgetClass = LoadClass<USelectWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Select/UI_Select.UI_Select_C'"));

	if (IsValid(WidgetClass))
	{
		mSelectWidget = CreateWidget<USelectWidget>(this, WidgetClass);

		if (IsValid(mSelectWidget))
		{
			mSelectWidget->AddToViewport();
		}
	}

	// EnhancedInput Subsystem을 얻어온다.
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// UPlatformInput 클래스의 CDO를 얻어온다.
	// GetDefault 함수는 <> 안에 들어가는 타입의 CDO를 얻어오는 함수이다. 
	// 이 함수는 const 클래스* 타입을 리턴한다.
	const USelectInput* InputCDO = GetDefault<USelectInput>();


	// Subsystem에 Context를 등록한다.
	Subsystem->AddMappingContext(InputCDO->mContext, 0);
}

void ASelectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(InputComponent);

	// 객체가 유효한지 검사한다.
	if (IsValid(EnhancedInput))
	{
		const USelectInput* InputCDO = GetDefault<USelectInput>();

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
		EnhancedInput->BindAction(InputCDO->mClick, ETriggerEvent::Started,
			this, &ASelectPlayerController::ClickKey);
	}
}

void ASelectPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 마우스가 선택할 캐릭터 위에 올라갔는지 체크한다.
	FHitResult	Hit;
	bool Collision = GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel6, true, Hit);

	if (Collision)
	{
		ASelectPawn* Hovered = Cast<ASelectPawn>(Hit.GetActor());

		// 기존에 마우스가 올라간 액터가 있을 경우
		if (mHoveredCharacter)
		{
			if (mHoveredCharacter != Hovered)
			{
				// 마우스 올라간것 해제처리
				mHoveredCharacter->EnableOutLine(false);
			}
		}

		if (Hovered)
		{
			Hovered->EnableOutLine(true);
			// 마우스가 올라간것을 표시한다.
			UE_LOG(LogUE20251, Warning, TEXT("Actor Select"));
		}

		mHoveredCharacter = Hovered;
	}

	else
	{
		if (mHoveredCharacter)
		{
			mHoveredCharacter->EnableOutLine(false);
			UE_LOG(LogUE20251, Warning, TEXT("Actor Release"));
			mHoveredCharacter = nullptr;
		}
	}
}

void ASelectPlayerController::ClickKey(const FInputActionValue& Value)
{
	if (mPickCharacter != mHoveredCharacter)
	{
		if (IsValid(mHoveredCharacter))
		{
			// 선택한 효과를 재생한다.
		}
	}

	mPickCharacter = mHoveredCharacter;

	if (IsValid(mSelectWidget))
	{
		mSelectWidget->EnableStartButton(mPickCharacter != nullptr);

		if (IsValid(mPickCharacter))
		{
			mSelectWidget->SetSelectJob(mPickCharacter->GetPlayerJob());
		}
	}
}
