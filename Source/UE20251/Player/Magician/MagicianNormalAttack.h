// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "MagicianNormalAttack.generated.h"

UCLASS()
class UE20251_API AMagicianNormalAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicianNormalAttack();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent>	mBody;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent>	mEffect;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>	mMovement;

	// 투사체를 발사한 컨트롤러를 가지고 있게 한다.
	class AController* mOwnerController;

	float mDamage = 0.f;

public:
	void SetDamage(float Damage)
	{
		mDamage = Damage;
	}

	void SetOwnerController(class AController* Controller)
	{
		mOwnerController = Controller;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ProjectileMovement를 이용하여 움직이는 물체가 다른 물체와 부딪혀서 더이상 움직일
	// 수 없을 때 호출되게 할 함수이다.
	UFUNCTION()
	void ProjectileStop(const FHitResult& Hit);
};
