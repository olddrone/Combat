// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CB_BaseCharacter.h"
#include "UI/Controller/CB_OverlayWidgetController.h"
#include "Data/EnemyState.h"
#include "CB_EnemyCharacter.generated.h"

class UGameplayEffect;
class UBehaviorTree;
class ACB_AIController;
class UCB_UserWidget;

UCLASS()
class COMBAT_API ACB_EnemyCharacter : public ACB_BaseCharacter
{
	GENERATED_BODY()
public:
	ACB_EnemyCharacter();
	void SetOutLine(bool bIsShow);
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintAssignable)
	FOnHealtChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealtChangedSignature OnMaxHealthChanged;
	
	virtual void Dead() override;

	virtual void SetWarpTarget() override;

	UFUNCTION()
	AActor* GetTargetActor() const { return TargetActor; }

	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* InTarget) { TargetActor = InTarget; }
	
	UFUNCTION(BlueprintCallable)
	void ActivateEnemy();

public:
	FORCEINLINE UCB_UserWidget* GetOverlay() const { return BossOverlay; }
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> InitStatEffect;

	UPROPERTY(EditAnywhere)
	float Level = 1.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACB_AIController> AIController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCB_UserWidget> BossOverlayClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCB_UserWidget> BossOverlay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Teleport;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsBoss = true;

};
