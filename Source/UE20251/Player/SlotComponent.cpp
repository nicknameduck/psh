// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotComponent.h"

USlotComponent::USlotComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}

void USlotComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USlotComponent::InitializeComponent()
{
	Super::InitializeComponent();

	mSlotList.Init(nullptr, mSlotMaxCount);
}

void USlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USlotComponent::AddSlot(USlotData* Data)
{
	// 꽉 찼을 경우
	if (mSlotCount == mSlotMaxCount)
	{
		return false;
	}

	// 인벤토리 칸 중에서 비어 있는 칸을 찾아서 아이템을 추가한다.
	for (int32 i = 0; i < mSlotMaxCount; ++i)
	{
		if (!IsValid(mSlotList[i]))
		{
			mSlotList[i] = Data;

			++mSlotCount;

			// ChangeDelegate에 등록된 함수가 있을 경우
			if (mChangeDelegate.IsBound())
			{
				mChangeDelegate.Broadcast(Data, i);
			}

			return true;
		}
	}

	return false;
}

void USlotComponent::UseItem(int32 Index)
{
}

void USlotComponent::SwapItem(int32 PrevIndex, int32 ChangeIndex)
{
	mSlotList.Swap(PrevIndex, ChangeIndex);

	// ChangeDelegate에 등록된 함수가 있을 경우
	if (mChangeDelegate.IsBound())
	{
		mChangeDelegate.Broadcast(mSlotList[PrevIndex], PrevIndex);
		mChangeDelegate.Broadcast(mSlotList[ChangeIndex], ChangeIndex);
	}
}

USlotData* USlotComponent::ChangeItem(USlotData* Data, int32 Index)
{
	USlotData* ReturnValue = mSlotList[Index];

	mSlotList[Index] = Data;

	if (mChangeDelegate.IsBound())
	{
		mChangeDelegate.Broadcast(mSlotList[Index], Index);
	}

	return ReturnValue;
}

void USlotComponent::RemoveItem(int32 Index)
{
	if (mSlotCount == 0)
	{
		return;
	}

	mSlotList[Index] = nullptr;

	--mSlotCount;

	// ChangeDelegate에 등록된 함수가 있을 경우
	if (mChangeDelegate.IsBound())
	{
		mChangeDelegate.Broadcast(nullptr, Index);
	}
}

void USlotComponent::ClearItem()
{
	for (int32 i = 0; i < mSlotMaxCount; ++i)
	{
		if (IsValid(mSlotList[i]))
		{
			mSlotList[i] = nullptr;

			if (mChangeDelegate.IsBound())
			{
				mChangeDelegate.Broadcast(nullptr, i);
			}
		}
	}

	mSlotCount = 0;
}

bool USlotComponent::CheckItem(int32 Index)
{
	return mSlotList[Index] != nullptr;
}

bool USlotComponent::IsFull()
{
	return mSlotCount == mSlotMaxCount;
}
