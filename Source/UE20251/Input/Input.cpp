// Fill out your copyright notice in the Description page of Project Settings.


#include "Input.h"

UPlatformInput::UPlatformInput()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMCPlatform.IMCPlatform'"));

	mContext = InputContext.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		MoveAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IAMove.IAMove'"));

	mMove = MoveAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		RotationAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IARotation.IARotation'"));

	mRotation = RotationAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		JumpAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IAJump.IAJump'"));

	mJump = JumpAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		AttackAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IAAttack.IAAttack'"));

	mAttack = AttackAction.Object;
}

UGameInput::UGameInput()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMGGame.IMGGame'"));

	mContext = InputContext.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		MoveAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IAMove.IAMove'"));

	mMove = MoveAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		RotationAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IARotation.IARotation'"));

	mRotation = RotationAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		JumpAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IAJump.IAJump'"));

	mJump = JumpAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		AttackAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IAAttack.IAAttack'"));

	mAttack = AttackAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		CameraRotationAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IACameraRotation.IACameraRotation'"));

	mCameraRotation = CameraRotationAction.Object;
}

USelectInput::USelectInput()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/Select/IMC_Select.IMC_Select'"));

	mContext = InputContext.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		ClickAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Select/IA_Click.IA_Click'"));

	mClick = ClickAction.Object;
}
