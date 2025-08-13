// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"
#include "../../UEAssetManager.h"
#include "ItemViewerWidget.h"
#include "IconWidget.h"
#include "ItemDataObject.h"
#include "../../Player/QuickSlotComponent.h"
#include "../../Player/InventoryComponent.h"
#include "SlotDragDrop.h"

USlotWidget::USlotWidget(const FObjectInitializer& ObjectInitializer) :
	UUserWidget(ObjectInitializer)
{
}

void USlotWidget::SetOwnerWidget(class UBaseUserWidget* OwnerWidget)
{
	mOwnerWidget = OwnerWidget;

	mSlotIcon->SetOwnerWidget(OwnerWidget);
}

void USlotWidget::SetSlotIndex(int32 Index)
{
	mSlotIndex = Index;

	mSlotIcon->SetSlotIndex(Index);
}

void USlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mSlotIcon = Cast<UIconWidget>(GetWidgetFromName(TEXT("UI_SlotIcon")));
	mSlotBack = Cast<UBorder>(GetWidgetFromName(TEXT("SlotBack")));
}

void USlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply USlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply	result;

	result.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 마우스 왼쪽 버튼이 눌러졌을 경우
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// 인벤토리 컴포넌트가 유효할 경우
		if (mSlotComponent)
		{
			// 이 슬롯의 인덱스에 아이템이 있을 경우
			if (mSlotComponent->CheckItem(mSlotIndex))
			{
				// 드래그를 감지시킨다.
				result = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this,
					EKeys::LeftMouseButton);


				UE_LOG(LogUE20251, Warning, TEXT("Mouse Down : %d"), mSlotIndex);
			}
		}
	}

	return result.NativeReply;
}

void USlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// Drag할 Operation이 없을 경우 만들어준다.
	if (!OutOperation)
	{
		USlotDragDrop* DragSlot = Cast<USlotDragDrop>(UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDrop::StaticClass()));

		OutOperation = DragSlot;

		if (IsValid(DragSlot))
		{
			DragSlot->mPrevSlotIndex = mSlotIndex;
			DragSlot->mPrevWidget = mOwnerWidget;
			DragSlot->mPrevSlotComponent = mSlotComponent;

			// 드래그를 할 때 화면에 출력하기 위한 슬롯위젯을 생성한다.
			USlotWidget* DragWidget = CreateWidget<USlotWidget>(GetWorld(), mDragWidgetClass);

			if (DragWidget)
			{
				DragWidget->SetSlotComponent(mSlotComponent);
				DragWidget->SetOwnerWidget(mOwnerWidget);
				DragWidget->SetSlotIndex(mSlotIndex);

				// 아이템 정보를 얻어온다.
				UItemDataObject* Item = mSlotComponent->GetItem<UItemDataObject>(mSlotIndex);

				// 보여지는 정보를 이 아이템의 정보로 화면에 보여질 수 있게 한다.
				DragWidget->ChangeItem(Item);
				// 슬롯의 틀은 보이지 않게 한다.
				//DragWidget->mSlotBack->SetVisibility(ESlateVisibility::Collapsed);
				DragWidget->mSlotBack->SetBrushColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
				// 드래그 되는 슬롯은 반투명하게 보이게 한다.
				DragWidget->mSlotIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.5f));

				// 드래그 되는 슬롯이 보여줄 위젯으로 위에서 설정한 위젯을 지정한다.
				DragSlot->DefaultDragVisual = DragWidget;

				// 출력될 드래그 위젯을 어디를 기준으로 보여줄지를 결정한다.
				DragSlot->Pivot = EDragPivot::MouseDown;
			}
		}
	}
}

bool USlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	
	USlotDragDrop* DragSlot = Cast<USlotDragDrop>(InOperation);

	if (DragSlot)
	{
		// 드래그한 슬롯의 부모 위젯을 얻어온다.
		USlotComponent* DragSlotComponent = DragSlot->mPrevSlotComponent;

		// 드래그한 슬롯과 현재 드롭한 슬롯이 같을 경우
		if (mSlotComponent == DragSlot->mPrevSlotComponent)
		{
			/*USlotData* SlotItem = DragSlotComponent->ChangeItem(mSlotComponent->GetItem<USlotData>(mSlotIndex), DragSlot->mPrevSlotIndex);*/

			// 드래그를 시작한 슬롯과 드롭한 슬롯이 서로 다를 경우 두 아이템의 위치를 바꿔준다.
			if (mSlotIndex != DragSlot->mPrevSlotIndex)
			{
				mSlotComponent->SwapItem(DragSlot->mPrevSlotIndex, mSlotIndex);
			}
		}

		else
		{
			// 1. 드래그한 슬롯이 퀵슬롯에 소속되어 있을 경우 드롭한 슬롯이 퀵슬롯이면 두위치를 서로 바꿔준다.
			// 2. 드래그한 슬롯이 퀵슬롯에 소속되어 있을 경우 드롭한 슬롯이 퀵슬롯이 아니라면 드래그한 퀵슬롯을
			// 비워준다.
			// 3. 드래그한 슬롯이 퀵슬롯이 아니고 
			UQuickSlotComponent* QuickSlot = Cast<UQuickSlotComponent>(DragSlot->mPrevSlotComponent);

			if (QuickSlot)
			{
				// 현재 Drop한 이 슬롯도 퀵슬롯일 경우
				UQuickSlotComponent* QuickSlotDest = Cast<UQuickSlotComponent>(mSlotComponent);

				if (QuickSlotDest)
				{
					QuickSlot->SwapItem(DragSlot->mPrevSlotIndex, mSlotIndex);
				}

				// 드롭한 곳이 퀵슬롯이 아니라면 드래그 한 퀵슬롯은 비워준다.
				else
				{
					QuickSlot->ChangeItem(nullptr, DragSlot->mPrevSlotIndex);
				}
			}

			else
			{
				// 현재 Drop한 이 슬롯이 퀵슬롯일 경우
				UQuickSlotComponent* QuickSlotDest = Cast<UQuickSlotComponent>(mSlotComponent);

				if (QuickSlotDest)
				{
					// 같은 아이템이 있는지 찾아서 같을 경우 자리를 옮겨준다.


					// 아닐경우 드래그 한 아이템을 퀵슬롯에 전달해준다.
					QuickSlotDest->ChangeItem(DragSlotComponent->GetItem<USlotData>(DragSlot->mPrevSlotIndex), mSlotIndex);

					//QuickSlot->SwapItem(DragSlot->mPrevSlotIndex, mSlotIndex);
				}

				// 드롭한 곳이 퀵슬롯이 아니라면 드래그 한 퀵슬롯은 비워준다.
				else
				{
					return false;
				}
			}
		}

		return true;
	}

	// 슬롯이 아닌 다른곳에 놓을 경우
	else
	{
		UQuickSlotComponent* QuickSlot = Cast<UQuickSlotComponent>(DragSlot->mPrevSlotComponent);

		if (QuickSlot)
		{
			DragSlot->mPrevSlotComponent->ChangeItem(nullptr, DragSlot->mPrevSlotIndex);
		}
	}

	return false;
}

void USlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	USlotDragDrop* DragSlot = Cast<USlotDragDrop>(InOperation);

	if (DragSlot)
	{
		UQuickSlotComponent* QuickSlot = Cast<UQuickSlotComponent>(DragSlot->mPrevSlotComponent);

		if (QuickSlot)
		{
			DragSlot->mPrevSlotComponent->ChangeItem(nullptr, DragSlot->mPrevSlotIndex);
		}
	}
}

void USlotWidget::ChangeItem(USlotData* Item)
{
	if (Item)
	{
		mSlotIcon->SetIconTexture(Item->GetSlotIcon());
		mSlotIcon->SetVisibility(ESlateVisibility::Visible);
	}

	// nullptr일 경우 이 칸을 비우겠다는 의미이다.
	else
	{
		mSlotIcon->SetIconTexture(nullptr);
		mSlotIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
}
