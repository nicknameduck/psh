// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusWidget.h"

UPlayerStatusWidget::UPlayerStatusWidget(const FObjectInitializer& ObjectInitializer) :
	UBaseUserWidget(ObjectInitializer)
{
	mWidgetName = TEXT("PlayerStatus");
}

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogUE20251, Warning, TEXT("UPlayerStatusWidget::NativeConstruct"));

	mTitleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	mCloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	mName = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerName")));
	mJob = Cast<UTextBlock>(GetWidgetFromName(TEXT("Job")));
	mAttack = Cast<UTextBlock>(GetWidgetFromName(TEXT("Attack")));
	mDefense = Cast<UTextBlock>(GetWidgetFromName(TEXT("Defense")));
	mHP = Cast<UTextBlock>(GetWidgetFromName(TEXT("HP")));
	mMP = Cast<UTextBlock>(GetWidgetFromName(TEXT("MP")));
	mAttackRange = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackRange")));
	mAttackSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackSpeed")));
	mMoveSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("MoveSpeed")));
	mLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("Level")));
	mExp = Cast<UTextBlock>(GetWidgetFromName(TEXT("Exp")));

	mCloseButton->OnClicked.AddDynamic(this, &UPlayerStatusWidget::CloseButtonClick);

	mTitleBar->OnPressed.AddDynamic(this, &UPlayerStatusWidget::TitleBarPress);
	mTitleBar->OnReleased.AddDynamic(this, &UPlayerStatusWidget::TitleBarRelease);
}

void UPlayerStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerStatusWidget::OpenUI()
{
	UE_LOG(LogUE20251, Warning, TEXT("UPlayerStatusWidget::OpenUI()"));
	ESlateVisibility CurrentVisibility = GetVisibility();

	switch (CurrentVisibility)
	{
		case ESlateVisibility::Visible:
			{
				SetVisibility(ESlateVisibility::Collapsed);
			}
			break;
		case ESlateVisibility::Collapsed:
		case ESlateVisibility::Hidden:
		case ESlateVisibility::HitTestInvisible:
		case ESlateVisibility::SelfHitTestInvisible:
			{
				SetVisibility(ESlateVisibility::Visible);
			}
			break;			
		default:
			break;
	}
}

void UPlayerStatusWidget::SetPlayerData(const FPlayerData& Data)
{
	mName->SetText(FText::FromString(Data.Name));

	switch (Data.Job)
	{
	case EPlayerJob::Warrior:
		mJob->SetText(FText::FromString(TEXT("전사")));
		break;
	case EPlayerJob::Assassin:
		mJob->SetText(FText::FromString(TEXT("암살자")));
		break;
	case EPlayerJob::Magician:
		mJob->SetText(FText::FromString(TEXT("마법사")));
		break;
	case EPlayerJob::Archer:
		mJob->SetText(FText::FromString(TEXT("궁수")));
		break;
	}

	mAttack->SetText(FText::FromString(FString::Printf(TEXT("공격력 : %d"), Data.Attack)));
	mDefense->SetText(FText::FromString(FString::Printf(TEXT("방어력 : %d"), Data.Defense)));
	mHP->SetText(FText::FromString(FString::Printf(TEXT("체력 : %d / %d"), Data.HP, Data.HPMax)));
	mMP->SetText(FText::FromString(FString::Printf(TEXT("마나 : %d / %d"), Data.MP, Data.MPMax)));
	mAttackRange->SetText(FText::FromString(FString::Printf(TEXT("공격거리 : %.2f"), Data.AttackRange)));
	mAttackSpeed->SetText(FText::FromString(FString::Printf(TEXT("공격속도 : %.2f"), Data.AttackSpeed)));
	mMoveSpeed->SetText(FText::FromString(FString::Printf(TEXT("이동속도 : %.2f"), Data.MoveSpeed)));
	mLevel->SetText(FText::FromString(FString::Printf(TEXT("레벨 : %d"), Data.Level)));
	mExp->SetText(FText::FromString(FString::Printf(TEXT("경험치 : %d"), Data.Exp)));
}

void UPlayerStatusWidget::SetHP(int32 HP, int32 HPMax)
{
	mHP->SetText(FText::FromString(FString::Printf(TEXT("체력 : %d / %d"), HP, HPMax)));
}

void UPlayerStatusWidget::SetMP(int32 MP, int32 MPMax)
{
	mMP->SetText(FText::FromString(FString::Printf(TEXT("마나 : %d / %d"), MP, MPMax)));
}

void UPlayerStatusWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPlayerStatusWidget::TitleBarPress()
{
	UBaseUserWidget* ParentWidget = Cast<UBaseUserWidget>(mParentWidget);

	if (ParentWidget)
	{
		ParentWidget->SetDragWidget(this);
		ParentWidget->SetFocusWidget(this);
	}
}

void UPlayerStatusWidget::TitleBarRelease()
{
	UBaseUserWidget* ParentWidget = Cast<UBaseUserWidget>(mParentWidget);

	if (ParentWidget)
	{
		ParentWidget->SetDragWidget(nullptr);
	}
}
