// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformItem.h"
#include "PlatformGameState.h"
#include "PlatFormPlayerState.h"

APlatformItem::APlatformItem()
{
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube_Center.Shape_Cube_Center'"));

	if (MeshAsset.Succeeded())
		mMesh->SetStaticMesh(MeshAsset.Object);

	mBody->SetBoxExtent(FVector(50.0, 50.0, 50.0));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mBody->SetCollisionProfileName(TEXT("Item"));
	
	// OnComponentHit : 블록이 될때 호출될 함수를 지정하는 델리게이트.
	// OnComponentBeginOverlap : 오버랩이 시작될 때 호출될 함수를 지정하는 델리게이트.
	// OnComponentEndOverlap : 오버랩이 끝날 때 호출될 함수를 지정하는 델리게이트.
	mBody->OnComponentHit.AddDynamic(this, &APlatformItem::BoxHit);
	mBody->OnComponentBeginOverlap.AddDynamic(this, &APlatformItem::BoxOverlap);
	mBody->OnComponentEndOverlap.AddDynamic(this, &APlatformItem::BoxEndOverlap);
}

// Called when the game starts or when spawned
void APlatformItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformItem::BoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
		TEXT("BoxHit"));
}

void APlatformItem::BoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
		TEXT("BoxOverlap"));

	// 아이템을 먹었을 경우 게임스테이트의 아이템 카운트를 1 감소시키고
	// 점수를 올려준다.
	APlatformGameState* GameState = GetWorld()->GetGameState<APlatformGameState>();

	if (GameState)
	{
		GameState->DeleteItem();
	}

	// 플레이어 스테이트는 플레이어 컨트롤러를 이용해서 꺼내온다.
	APlayerController* Control = GetWorld()->GetFirstPlayerController();

	if (Control)
	{
		// 템플릿 타입에 타입을 지정하고 플레이어 스테이트를 얻어온다.
		APlatformPlayerState* State = Control->GetPlayerState<APlatformPlayerState>();

		if (State)
			State->AddScore(mScore);
	}

	// 이 액터를 제거한다.
	Destroy();
}

void APlatformItem::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue,
		TEXT("BoxEndOverlap"));
}

