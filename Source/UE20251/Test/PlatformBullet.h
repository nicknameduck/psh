// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "PlatformBullet.generated.h"

UCLASS()
class UE20251_API APlatformBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformBullet();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>		mBody;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>	mMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>	mMovement;

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
