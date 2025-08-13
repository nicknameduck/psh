// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Planet.generated.h"

UCLASS()
class UE20251_API APlanet : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlanet();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>	mSun;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>	mSunRotation;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>	mEarth;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>	mEarthRotation;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>	mMoon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent>	mSunRotMove;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent>	mEarthRotMove;

	// UProjectileMovementComponent : Actor 클래스 종류들이 사용할 수 있는 이동 컴포넌트.
	// URotatingMovementComponent : Actor 클래스 종류들이 사용할 수 있는 이동 컴포넌트.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent>	mMoonRotMove;

	// UFloatingPawnMovement : Pawn 클래스 종류들만 사용할 수 있는 이동 컴포넌트.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFloatingPawnMovement>	mMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
