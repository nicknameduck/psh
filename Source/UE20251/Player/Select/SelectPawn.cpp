// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPawn.h"

ASelectPawn::ASelectPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);

	mBody->SetCapsuleHalfHeight(92.f);
	mBody->SetCapsuleRadius(32.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -92.0));
	mBody->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));

	mBody->SetCollisionProfileName(TEXT("Select"));

	mBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mJob = EPlayerJob::Warrior;
}

void ASelectPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASelectPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASelectPawn::EnableOutLine(bool Enable)
{
	if (Enable)
	{
		mMesh->SetCustomDepthStencilValue(1);
	}

	else
	{
		mMesh->SetCustomDepthStencilValue(0);
	}
}
