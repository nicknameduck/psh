#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Engine/DamageEvents.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"


#include "Components/WidgetComponent.h"


#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUE20251, Warning, All);

// Team : 0 ~ 255 사이의 값
#define	TeamNeutral	255
#define	TeamMonster	30
#define	TeamPlayer	1

FRotator GetTargetRotation(const FVector& Target, const FVector& Current);
FRotator GetTargetRotationYaw(FVector Target, FVector Current);


UENUM(BlueprintType)
enum class EPlayerAnim : uint8
{
	Locomotion
};

// 데이터 테이블용 구조체를 만드는 경우 반드시 FTableRowBase 를 상속받아야 한다.
USTRUCT(BlueprintType)
struct FPlayerAnimInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UAnimSequence>>	SequenceMap;

	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UBlendSpace>>	BlendSpaceMap;

	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UAnimMontage>>	MontageMap;

	UPROPERTY(EditAnywhere)
	TArray<FName>							AttackSectionArray;
};

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	Warrior,
	Magician,
	Archer,
	Assassin
};

USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EPlayerJob	Job;

	UPROPERTY(EditAnywhere)
	int32		Attack;

	UPROPERTY(EditAnywhere)
	int32		Defense;

	UPROPERTY(EditAnywhere)
	int32		HP;

	UPROPERTY(EditAnywhere)
	int32		MP;

	UPROPERTY(EditAnywhere)
	float		AttackRange;

	UPROPERTY(EditAnywhere)
	float		AttackSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float		MoveSpeed = 600.f;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString		Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerJob	Job;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		Defense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		HPMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		MP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		MPMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		AttackSpeed = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		MoveSpeed = 600.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		Exp = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		Gold = 10000;
};

USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString		Name;

	UPROPERTY(EditAnywhere)
	int32		Attack;

	UPROPERTY(EditAnywhere)
	int32		Defense;

	UPROPERTY(EditAnywhere)
	int32		HP;

	UPROPERTY(EditAnywhere)
	int32		MP;

	UPROPERTY(EditAnywhere)
	float		AttackRange;

	UPROPERTY(EditAnywhere)
	float		AttackSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float		MoveSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float		DetectRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float		ViewHalfAngle = 45.f;

	UPROPERTY(EditAnywhere)
	int32		Level;

	UPROPERTY(EditAnywhere)
	int32		Exp;

	UPROPERTY(EditAnywhere)
	int32		Gold;
};

USTRUCT(BlueprintType)
struct FMonsterData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString		Name;

	UPROPERTY(EditAnywhere)
	int32		Attack;

	UPROPERTY(EditAnywhere)
	int32		Defense;

	UPROPERTY(EditAnywhere)
	int32		HP;

	UPROPERTY(EditAnywhere)
	int32		HPMax;

	UPROPERTY(EditAnywhere)
	int32		MP;

	UPROPERTY(EditAnywhere)
	int32		MPMax;

	UPROPERTY(EditAnywhere)
	float		AttackRange;

	UPROPERTY(EditAnywhere)
	float		AttackSpeed = 1.f;

	UPROPERTY(EditAnywhere)
	float		MoveSpeed = 600.f;

	UPROPERTY(EditAnywhere)
	float		DetectRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float		ViewHalfAngle = 45.f;

	UPROPERTY(EditAnywhere)
	int32		Level;

	UPROPERTY(EditAnywhere)
	int32		Exp;

	UPROPERTY(EditAnywhere)
	int32		Gold;
};

USTRUCT(BlueprintType)
struct FMonsterAnim : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FName, TObjectPtr<UAnimSequence>>	SequenceMap;
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Armor,
	Etc
};

UENUM(BlueprintType)
enum class EItemSubType : uint8
{
	Sword,
	Bow,
	Wand,
	Gun,
	Spear,
	Armor,
	Shoes,
	Gloves,
	HPPotion,
	MPPotion
};

UENUM(BlueprintType)
enum class EItemOptionType : uint8
{
	Attack,
	Defense,
	HPMax,
	HPRecovery,
	MPMax,
	MPRecovery,
	MoveSpeed,
	AttackSpeed,
	AttackDistance,
	CriticalRatio,
	CriticalDamage
};

USTRUCT(BlueprintType)
struct FItemOption
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EItemOptionType	Type;

	UPROPERTY(EditAnywhere)
	float	Option;
};


USTRUCT(BlueprintType)
struct FItemTableInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EItemType	Type;

	UPROPERTY(EditAnywhere)
	EItemSubType	SubType;

	UPROPERTY(EditAnywhere)
	FString	ItemName;

	UPROPERTY(EditAnywhere)
	FString	Desc;

	UPROPERTY(EditAnywhere)
	int32	Price;

	UPROPERTY(EditAnywhere)
	int32	Sell;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<FItemOption>	OptionArray;
};

struct FItemData
{
public:
	EItemType	Type;
	EItemSubType	SubType;
	FString	ItemName;
	FString	Desc;
	int32	Price;
	int32	Sell;
	UTexture2D* Icon;
	USkeletalMesh* Mesh;
	TArray<FItemOption>	OptionArray;
};

FString GetItemOptionName(EItemOptionType Option);
