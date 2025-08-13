// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlotData.h"
#include "Components/ActorComponent.h"
#include "SlotComponent.generated.h"

// 슬롯에 변화가 생길때마다 호출해줄 함수를 등록하기 위한 델리게이트를 만들어준다.
DECLARE_MULTICAST_DELEGATE_TwoParams(FSlotChange, UObject*, int32);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE20251_API USlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USlotComponent();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<USlotData>>	mSlotList;

	// 저장 가능한 아이템 최대 수
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32		mSlotMaxCount = 35;

	// 현재 추가된 아이템 수
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32		mSlotCount = 0;

public:
	template <typename T>
	T* GetItem(int32 Index)
	{
		return Cast<T>(mSlotList[Index]);
	}

	int32 GetMaxCount()	const
	{
		return mSlotMaxCount;
	}

	int32 GetCount()	const
	{
		return mSlotCount;
	}

public:
	FSlotChange	mChangeDelegate;

protected:
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool AddSlot(USlotData* Data);
	void UseItem(int32 Index);
	void SwapItem(int32 PrevIndex, int32 ChangeIndex);
	USlotData* ChangeItem(USlotData* Data, int32 Index);
	void RemoveItem(int32 Index);
	void ClearItem();
	void SetGold(int32 Gold);
	bool CheckItem(int32 Index);
	bool IsFull();
};
