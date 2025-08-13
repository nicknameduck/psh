// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerDefaultAnimInstance.h"
#include "PlayerTemplateAnimInstance.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE20251_API APlayerCharacter : public ACharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent>		mSpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent>		mCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D>	mCaptureCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent>		mHeadUpWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInventoryComponent>	mInventory;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UQuickSlotComponent>	mQuickSlot;

	TObjectPtr<class UHeadUpInfoWidget>	mHeadUpWidgetObject;

	//TObjectPtr<UPlayerDefaultAnimInstance>	mAnimInst;
	TObjectPtr<UPlayerTemplateAnimInstance>		mAnimInst;

	TSubclassOf<AActor>		mStatusPictureClass;

	FName			mDatakey;

	FGenericTeamId	mTeamID;

public:
	class UInventoryComponent* GetInventoryComponent()	const
	{
		return mInventory;
	}

	class UQuickSlotComponent* GetQuickSlotComponent()	const
	{
		return mQuickSlot;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void MoveKey(const FInputActionValue& Value);
	void RotationKey(const FInputActionValue& Value);
	void JumpKey(const FInputActionValue& Value);
	void AttackKey(const FInputActionValue& Value);
	void CameraRotationKey(const FInputActionValue& Value);

public:
	virtual void NormalAttack();




public:
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId()	const;
};
