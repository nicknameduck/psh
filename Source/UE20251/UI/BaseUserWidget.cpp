// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"
#include "UIManager.h"

UBaseUserWidget::UBaseUserWidget(const FObjectInitializer& ObjectInitializer)	:
	UUserWidget(ObjectInitializer)	// 부모클래스의 생성자를 ObjectInitializer를 사용하는 생성자 호출
{
}

void UBaseUserWidget::PlayWidgetAnimation(const FString& Name, float PlayStartTime, float PlaySpeed, bool Forward, bool RestoreState, int32 LoopCount)
{
	TObjectPtr<UWidgetAnimation>	Anim = mAnimMap.FindRef(Name);

	if (IsValid(Anim))
	{
		EUMGSequencePlayMode::Type	PlayMode = EUMGSequencePlayMode::Forward;

		if (!Forward)
			PlayMode = EUMGSequencePlayMode::Reverse;

		PlayAnimation(Anim, PlayStartTime, LoopCount, PlayMode, PlaySpeed, RestoreState);
	}
}

void UBaseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CUIManager::GetInst()->AddWidget(mWidgetName, this);
}

void UBaseUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 애니메이션을 가지고 있는 위젯트리를 얻어온다.
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	// TArray로 되어 있는 애니메이션을 반복하며 Map에 넣어준다.
	for (auto& Anim : WidgetClass->Animations)
	{
		// StartButtonHovered_INST 이렇게 나오기 때문에 _INST를 제거할 것이다.
		FString	Name = Anim->GetName();

		Name.ReplaceInline(TEXT("_INST"), TEXT(""), ESearchCase::IgnoreCase);

		mAnimMap.Add(Name, Anim);
	}

	bIsFocusable = true;
}

void UBaseUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	CUIManager::GetInst()->DeleteWidget(mWidgetName);
}

void UBaseUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 드래그 하고 있는 위젯이 있을 경우
	if (mDragWidget)
	{
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(mDragWidget->Slot);

		if (CanvasSlot)
		{
			// 현재 뷰포트 상에서의 마우스 위치를 얻어온다.
			FVector2D	MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

			// 이전 마우스 위치와 현재 마우스 위치를 비교하여 얼마나 움직였는지 값을 구한다.
			FVector2D	MouseOffset = MousePos - mDragPrevMousePos;

			// 현재 위치가 다음 프레임에서는 이전위치가 된다.
			mDragPrevMousePos = MousePos;

			// 현재 위젯의 위치를 얻어온다.
			FVector2D	WidgetPos = CanvasSlot->GetPosition();

			// 최종 위치는 현재 위치 + 오프셋이다.
			CanvasSlot->SetPosition(WidgetPos + MouseOffset);
		}
	}
}

int32 UBaseUserWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 Result = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	//UE_LOG(LogUE20251, Warning, TEXT("NativePaint"));

	return Result;
}

bool UBaseUserWidget::NativeIsInteractable() const
{
	bool Result = Super::NativeIsInteractable();

	UE_LOG(LogUE20251, Warning, TEXT("NativeIsInteractable"));

	return Result;
}

bool UBaseUserWidget::NativeSupportsKeyboardFocus() const
{
	bool Result = Super::NativeSupportsKeyboardFocus();

	//UE_LOG(LogUE20251, Warning, TEXT("NativeSupportsKeyboardFocus"));

	return Result;
}

FReply UBaseUserWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply Result = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnFocusReceived"));

	return Result;
}

void UBaseUserWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnFocusLost"));
}

void UBaseUserWidget::NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnFocusChanging"));
}

void UBaseUserWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnAddedToFocusPath"));
}

void UBaseUserWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnRemovedFromFocusPath"));
}

FNavigationReply UBaseUserWidget::NativeOnNavigation(const FGeometry& MyGeometry, const FNavigationEvent& InNavigationEvent, const FNavigationReply& InDefaultReply)
{
	FNavigationReply Result = Super::NativeOnNavigation(MyGeometry, InNavigationEvent, InDefaultReply);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnNavigation"));

	return Result;
}

FReply UBaseUserWidget::NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent)
{
	FReply Result = Super::NativeOnKeyChar(InGeometry, InCharEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnKeyChar"));

	return Result;
}

FReply UBaseUserWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnPreviewKeyDown"));

	return Result;
}

FReply UBaseUserWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnKeyDown"));

	return Result;
}

FReply UBaseUserWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnKeyUp"));

	return Result;
}

FReply UBaseUserWidget::NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent)
{
	FReply Result = Super::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnAnalogValueChanged"));

	return Result;
}

FReply UBaseUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseButtonDown"));

	return FReply::Handled();
}

FReply UBaseUserWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnPreviewMouseButtonDown"));

	return Result;
}

FReply UBaseUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseButtonUp"));

	return Result;
}

FReply UBaseUserWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	//UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseMove"));

	return Result;
}

void UBaseUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseEnter"));
}

void UBaseUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseLeave"));
}

FReply UBaseUserWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseWheel"));

	return Result;
}

FReply UBaseUserWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseButtonDoubleClick"));

	return Result;
}

void UBaseUserWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnDragDetected"));
}

void UBaseUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnDragEnter"));
}

void UBaseUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnDragLeave"));
}

bool UBaseUserWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnDragOver"));

	return Result;
}

bool UBaseUserWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnDrop"));

	return Result;
}

void UBaseUserWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnDragCancelled"));
}

FReply UBaseUserWidget::NativeOnTouchGesture(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Result = Super::NativeOnTouchGesture(InGeometry, InGestureEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnTouchGesture"));

	return Result;
}

FReply UBaseUserWidget::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Result = Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnTouchStarted"));

	return Result;
}

FReply UBaseUserWidget::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Result = Super::NativeOnTouchMoved(InGeometry, InGestureEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnTouchMoved"));

	return Result;
}

FReply UBaseUserWidget::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
	FReply Result = Super::NativeOnTouchEnded(InGeometry, InGestureEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnTouchEnded"));

	return Result;
}

FReply UBaseUserWidget::NativeOnMotionDetected(const FGeometry& InGeometry, const FMotionEvent& InMotionEvent)
{
	FReply Result = Super::NativeOnMotionDetected(InGeometry, InMotionEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMotionDetected"));

	return Result;
}

FReply UBaseUserWidget::NativeOnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent)
{
	FReply Result = Super::NativeOnTouchForceChanged(MyGeometry, TouchEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnTouchForceChanged"));

	return Result;
}

FCursorReply UBaseUserWidget::NativeOnCursorQuery(const FGeometry& InGeometry, const FPointerEvent& InCursorEvent)
{
	FCursorReply Result = Super::NativeOnCursorQuery(InGeometry, InCursorEvent);

	//UE_LOG(LogUE20251, Warning, TEXT("NativeOnCursorQuery"));

	return Result;
}

FNavigationReply UBaseUserWidget::NativeOnNavigation(const FGeometry& InGeometry, const FNavigationEvent& InNavigationEvent)
{
	FNavigationReply Result = Super::NativeOnNavigation(InGeometry, InNavigationEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnNavigation"));

	return Result;
}

void UBaseUserWidget::NativeOnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent)
{
	Super::NativeOnMouseCaptureLost(CaptureLostEvent);

	UE_LOG(LogUE20251, Warning, TEXT("NativeOnMouseCaptureLost"));
}

void UBaseUserWidget::NativeOnFinishedPointerInput()
{
	Super::NativeOnFinishedPointerInput();

	//UE_LOG(LogUE20251, Warning, TEXT("NativeOnFinishedPointerInput"));
}
