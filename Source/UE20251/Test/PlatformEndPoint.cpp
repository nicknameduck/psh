// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformEndPoint.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlatformEndPoint::APlatformEndPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	SetRootComponent(mBody);

	mBody->SetCollisionProfileName(TEXT("Item"));

	mBody->OnComponentBeginOverlap.AddDynamic(this, &APlatformEndPoint::BoxOverlap);
}

// Called when the game starts or when spawned
void APlatformEndPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlatformEndPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformEndPoint::BoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr,
		EQuitPreference::Quit, false);
}
