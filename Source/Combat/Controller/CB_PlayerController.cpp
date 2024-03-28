// Fill out your copyright notice in the Description page of Project Settings.

#include "CB_PlayerController.h"
#include "../Data/CB_PDA_Input.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "../Character/CB_PlayerCharacter.h"

void ACB_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputData->MappingContext, 0);
	}
}

void ACB_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &ACB_PlayerController::Move);
		EIC->BindAction(InputData->LookAction, ETriggerEvent::Triggered, this, &ACB_PlayerController::Look);
		
		EIC->BindAction(InputData->JumpAction, ETriggerEvent::Triggered, this, &ACB_PlayerController::GASInputPressed<0>);
		EIC->BindAction(InputData->JumpAction, ETriggerEvent::Completed, this, &ACB_PlayerController::GASInputReleased<0>);
		EIC->BindAction(InputData->AttackAction, ETriggerEvent::Triggered, this, &ACB_PlayerController::GASInputPressed<1>);
		EIC->BindAction(InputData->DodgeAction, ETriggerEvent::Triggered, this, &ACB_PlayerController::GASInputPressed<2>);

	}
}

void ACB_PlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
}

void ACB_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	GetCharacter()->AddControllerYawInput(LookAxisVector.X);
	GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);
}

void ACB_PlayerController::GASInputPressed(uint32 Idx)
{
	ACB_PlayerCharacter* PlayerCharacter = Cast<ACB_PlayerCharacter>(GetCharacter());
	PlayerCharacter->GASInputPressed(Idx);
}

void ACB_PlayerController::GASInputReleased(uint32 Idx)
{
	ACB_PlayerCharacter* PlayerCharacter = Cast<ACB_PlayerCharacter>(GetCharacter());
	PlayerCharacter->GASInputReleased(Idx);
}
