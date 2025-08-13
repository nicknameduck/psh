// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformBullet.h"

APlatformBullet::APlatformBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);

	mMovement->SetUpdatedComponent(RootComponent);

	mBody->SetCollisionProfileName(TEXT("BlockAll"));

	mMovement->InitialSpeed = 2000.f;

	mMovement->ProjectileGravityScale = 1.f;

	mMovement->OnProjectileStop.AddDynamic(this, &APlatformBullet::ProjectileStop);
	//mMovement->OnProjectileBounce

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Sphere_Center.Sphere_Center'"));

	if (MeshAsset.Succeeded())
		mMesh->SetStaticMesh(MeshAsset.Object);

	mBody->SetSphereRadius(50.f);
}

void APlatformBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
언리얼 충돌 시스템
Ignore, Overlap, Block 3가지 충돌 상태가 있다.
Ignore : 충돌을 무시한다.
Overlap : 충돌은 하지만 겹쳐지는것을 허용한다.
Block : 충돌을 하며 충돌하는 순간 겹쳐지지 않게 밀어낸다.
*/
void APlatformBullet::ProjectileStop(const FHitResult& Hit)
{
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Hit"));
}

