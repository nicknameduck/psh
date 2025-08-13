// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWidget.h"

USelectWidget::USelectWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("Select");
}


void USelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	mInputName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputName")));

	mStartButton->OnClicked.AddDynamic(this, &USelectWidget::StartClick);

	mInputName->OnTextCommitted.AddDynamic(this, &USelectWidget::TextCommit);
}

void USelectWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void USelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}

void USelectWidget::StartClick()
{
	// 다른 레벨을 열어줄 때 정보를 넘기는 방법은 여러가지 방법이 있다.
	// 1. GameInstance는 게임 종료시 제거되기 때문에 여기에 데이터를 넣어두고 원할 때 가져다 사용한다.
	// 2. OpenLevel의 Option String을 이용해서 다른 레벨을 열어줄 때 데이터를 전달할 수 있다.
	// 3. 파일에 저장했다가 불러올 수 있다.
	// 4. 서버에 보내놨다가 다시 받아서 사용할 수 있다.
	// 옵션스트링 마지막은 한칸 공백을 준다.
	FString	OptionString = FString::Printf(TEXT("Job=%d MapName=Main MapPath=/Game/Maps/Main PlayerName=%s "), (int32)mSelectJob, *mInputName->GetText().ToString());

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Loading"), true, OptionString);
}

void USelectWidget::TextCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter && mStartButton->GetIsEnabled())
	{
		StartClick();
	}
}
