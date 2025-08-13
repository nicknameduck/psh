// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformEndPoint.generated.h"

UCLASS()
class UE20251_API APlatformEndPoint : public AActor
{
	GENERATED_BODY()
	
public:
	APlatformEndPoint();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent>	mBody;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void BoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
