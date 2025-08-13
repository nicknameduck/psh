
#include "GameInfo.h"

DEFINE_LOG_CATEGORY(LogUE20251);

FRotator GetTargetRotation(const FVector& Target, const FVector& Current)
{
    return UKismetMathLibrary::FindLookAtRotation(Current, Target);
}

FRotator GetTargetRotationYaw(FVector Target, FVector Current)
{
    Current.Z = 0.0;
    Target.Z = 0.0;

    return UKismetMathLibrary::FindLookAtRotation(Current, Target);
}

FString GetItemOptionName(EItemOptionType Option)
{
	switch (Option)
	{
	case EItemOptionType::Attack:
		return TEXT("공격력");
	case EItemOptionType::Defense:
		return TEXT("방어력");
	case EItemOptionType::HPMax:
		return TEXT("최대체력");
	case EItemOptionType::HPRecovery:
		return TEXT("체력회복");
	case EItemOptionType::MPMax:
		return TEXT("최대마나");
	case EItemOptionType::MPRecovery:
		return TEXT("마나회복");
	case EItemOptionType::MoveSpeed:
		return TEXT("이동속도");
	case EItemOptionType::AttackSpeed:
		return TEXT("공격속도");
	case EItemOptionType::AttackDistance:
		return TEXT("공격거리");
	case EItemOptionType::CriticalRatio:
		return TEXT("치명확률");
	case EItemOptionType::CriticalDamage:
		return TEXT("치명데미지");
	}
	
	return TEXT("");
}
