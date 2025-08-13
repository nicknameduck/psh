// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianNormalAttack.h"
#include "../../Monster/MonsterMovement.h"

// Sets default values
AMagicianNormalAttack::AMagicianNormalAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	mEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	mMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mBody);

	mEffect->SetupAttachment(mBody);

	mMovement->SetUpdatedComponent(mBody);

	mEffect->SetRelativeLocation(FVector(50.0, 0.0, 0.0));
	mEffect->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));

	mBody->SetBoxExtent(FVector(45.0, 20.0, 20.0));

	mBody->SetCollisionProfileName(TEXT("PlayerAttack"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>
		EffectAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/AdvancedMagicFX13/Particles/Niagara/NS_ky_stabShot.NS_ky_stabShot'"));

	if (EffectAsset.Succeeded())
		mEffect->SetAsset(EffectAsset.Object);

	mMovement->ProjectileGravityScale = 0.f;
	mMovement->InitialSpeed = 1000.f;

	mMovement->OnProjectileStop.AddDynamic(this, &AMagicianNormalAttack::ProjectileStop);
}

// Called when the game starts or when spawned
void AMagicianNormalAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicianNormalAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicianNormalAttack::ProjectileStop(const FHitResult& Hit)
{
	// 넉백 적용.
	APawn* DestPawn = Cast<APawn>(Hit.GetActor());

	if (DestPawn)
	{
		UMonsterMovement* Movement = Cast<UMonsterMovement>(DestPawn->GetMovementComponent());

		if (Movement)
		{
			Movement->AddKnockbackImpulse(GetActorForwardVector() * 1000.f);
		}
	}

	FDamageEvent	DmgEvent;

	Hit.GetActor()->TakeDamage(mDamage, DmgEvent, mOwnerController, this);


	// 나이이가라 파티클 로딩.
	UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(GetWorld(), TEXT("/Script/Niagara.NiagaraSystem'/Game/AdvancedMagicFX13/Particles/Niagara/NS_ky_hit_slash.NS_ky_hit_slash'"));

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Hit.ImpactPoint);

	USoundBase* Sound = LoadObject<USoundBase>(GetWorld(), TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, Hit.ImpactPoint);

	Destroy();
}

