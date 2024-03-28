// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CB_BaseCharacter.generated.h"


UCLASS()
class COMBAT_API ACB_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACB_BaseCharacter();

public:
	FORCEINLINE virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override 
	{ return ASC; }
	FORCEINLINE virtual class UAnimMontage* GetLightAttackMontage() const { return LightAttackMontage; }
	FORCEINLINE virtual class UAnimMontage* GetDodgeMontage() const { return DodgeMontage; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UAbilitySystemComponent> ASC = nullptr;

	UPROPERTY(EditAnywhere, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TMap<int32, TSubclassOf<class UGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> LightAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DodgeMontage;

};
