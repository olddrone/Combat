// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_AttackAbility.h"
#include "../Character/CB_BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"

UCB_AttackAbility::UCB_AttackAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCB_AttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACB_BaseCharacter* CBCharacter = CastChecked<ACB_BaseCharacter>(ActorInfo->AvatarActor.Get());

	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("PlayAttack"), CBCharacter->GetLightAttackMontage(), 1.0f, GetNextSection());
	PlayAttackTask->OnCompleted.AddDynamic(this, &UCB_AttackAbility::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &UCB_AttackAbility::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();

}

void UCB_AttackAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// �ִ� ��Ƽ���� ������Ʈ���� bool ���� true��, �ٷ� ���� ��Ÿ�� ����
	UE_LOG(LogTemp, Warning, TEXT("asdf"));
}

void UCB_AttackAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UCB_AttackAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UCB_AttackAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UCB_AttackAbility::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

FName UCB_AttackAbility::GetNextSection()
{
	// ���߿� ��Ƽ���̿��� ó��
	(Combo < 3) ? ++Combo : Combo = 1;
	FName NextSection = *FString::Printf(TEXT("Attack%d"), Combo);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *NextSection.ToString());
	return NextSection;
}

