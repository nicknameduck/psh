// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"
#include "UEPlayerState.h"

AWarrior::AWarrior()
{
	mDatakey = TEXT("Warrior");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangAlbino.KwangAlbino'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMeshAsset(MeshAsset.Object);

	mHeadUpWidget->SetRelativeLocation(FVector(0.0, 0.0, 190.0));

	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -94.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	// 클래스 정보를 읽어올 경우 경로의 가장 끝에 _C를 무조건 붙여야 한다.
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/Warrior/ABPWarrior.ABPWarrior_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	static ConstructorHelpers::FClassFinder<AActor>
		StatusPictureClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BPStatusPicture_Warrior.BPStatusPicture_Warrior_C'"));

	if (StatusPictureClass.Succeeded())
		mStatusPictureClass = StatusPictureClass.Class;
}

void AWarrior::NormalAttack()
{
	AUEPlayerState* State = GetPlayerState<AUEPlayerState>();

	const FPlayerData& Data = State->GetPlayerData();

	FVector	Forward = GetActorForwardVector();

	FVector	HitStart = GetActorLocation() + Forward * 50.f;
	FVector	Center = GetActorLocation() + Forward * (50.f + Data.AttackRange / 2.f);

	TArray<FHitResult>	result;

	FCollisionQueryParams	param;
	param.AddIgnoredActor(this);
	param.bTraceComplex = false;

	bool Collision = GetWorld()->SweepMultiByChannel(result, Center, Center,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(100.f), param);

	//DrawDebugAltCone

	if (Collision)
	{
		float	Origin = FMath::Cos(FMath::DegreesToRadians(45.f));

		for (auto& Hit : result)
		{
			FVector	HitLocation = Hit.GetActor()->GetActorLocation();

			// 충돌 시작점에서 충돌 검출된 액터의 위치를 향하는 방향을 구한다.
			FVector	Dir = HitLocation - HitStart;
			Dir.Normalize();

			// 공격 방향과 위의 방향을 이용하여 각도의 코사인 값을 구한다.
			float Angle = Dir.Dot(Forward);

			if (Angle >= Origin)
			{
				// 공격처리.
				FDamageEvent	DmgEvent;
				Hit.GetActor()->TakeDamage(Data.Attack, DmgEvent, GetController(), this);

				// 파티클 로딩.
				UParticleSystem* Particle = LoadObject<UParticleSystem>(GetWorld(), TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact'"));

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle,
					Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

				// 나이이가라 파티클 로딩.
				UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(GetWorld(), TEXT("/Script/Niagara.NiagaraSystem'/Game/AdvancedMagicFX13/Particles/Niagara/NS_ky_burst.NS_ky_burst'"));

				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Hit.ImpactPoint);

				USoundBase* Sound = LoadObject<USoundBase>(GetWorld(), TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));

				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, Hit.ImpactPoint);
			}
		}
	}
}
