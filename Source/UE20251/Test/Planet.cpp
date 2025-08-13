// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"

/*
언리얼 C++ 클래스는 Actor의 경우 에디터에 배치하는 순간 생성자가 호출이 된다.

*/
APlanet::APlanet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트를 생성한다.
	mSun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sun"));
	mSunRotation = CreateDefaultSubobject<USceneComponent>(TEXT("SunRotation"));
	mEarth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Earth"));
	mEarthRotation = CreateDefaultSubobject<USceneComponent>(TEXT("EarthRotation"));
	mMoon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Moon"));

	mSunRotMove = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("SunRotMove"));
	mEarthRotMove = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("EarthRotMove"));
	mMoonRotMove = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("MoonRotMove"));

	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	// 루트컴포넌트를 지정한다.
	SetRootComponent(mSun);

	// SunRotation을 Sun의 자식컴포넌트로 지정한다.
	mSunRotation->SetupAttachment(mSun);
	mEarth->SetupAttachment(mSunRotation);
	mEarthRotation->SetupAttachment(mSunRotation);
	mMoon->SetupAttachment(mEarthRotation);

	// RotatingMovementComponent가 회전시켜줄 대상 Component를 지정한다.
	mSunRotMove->SetUpdatedComponent(mSunRotation);
	mEarthRotMove->SetUpdatedComponent(mEarth);
	mMoonRotMove->SetUpdatedComponent(mEarthRotation);

	// RootComponent를 이동시켜 모든 Component가 이동되게 한다.
	mMovement->SetUpdatedComponent(RootComponent);

	// Pitch : Y축회전
	// Yaw : Z축회전
	// Roll : X축회전
	mSunRotMove->RotationRate = FRotator(0.0, 60.0, 0.0);
	mEarthRotMove->RotationRate = FRotator(0.0, 100.0, 0.0);
	mMoonRotMove->RotationRate = FRotator(0.0, 130.0, 0.0);

	// ConstructorHelpers에서 제공하는 애셋 로딩 기능은 오로지 클래스 생성자에서만
	// 사용이 가능하다. <> 템플릿 타입에는 로딩하고자 하는 애셋 타입을 지정한다.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_CornerFrame.SM_CornerFrame'"));

	if (MeshAsset.Succeeded())
	{
		// MeshAsset.Object : 로딩된 메시가 들어가있는 변수.
		mSun->SetStaticMesh(MeshAsset.Object);
		mEarth->SetStaticMesh(MeshAsset.Object);
		mMoon->SetStaticMesh(MeshAsset.Object);
	}

	mEarth->SetRelativeLocation(FVector(380.0, 0.0, 0.0));
	mEarthRotation->SetRelativeLocation(FVector(380.0, 0.0, 0.0));
	mMoon->SetRelativeLocation(FVector(110.0, 0.0, 0.0));

	mEarth->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	mMoon->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	// Super : 부모클래스
	Super::BeginPlay();
	
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mMovement->AddInputVector(GetActorForwardVector());
}

// Called to bind functionality to input
void APlanet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

