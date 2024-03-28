// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CB_PlayerController.generated.h"

struct FInputActionValue;
class UCB_PDA_Input;

/**
 * 
 */
UCLASS()
class COMBAT_API ACB_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void GASInputPressed(uint32 Idx);
	template<int32 Idx>
	void GASInputPressed() { GASInputPressed(Idx); }
	
	void GASInputReleased(uint32 Idx);
	template<int32 Idx>
	void GASInputReleased() { GASInputReleased(Idx); }

private:
	UPROPERTY(EditAnywhere, Category = "Data")
	TObjectPtr<UCB_PDA_Input> InputData = nullptr;
};
