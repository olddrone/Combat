// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_DodgeAbility.h"
#include "../Character/CB_BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/CharacterMovementComponent.h"

UCB_DodgeAbility::UCB_DodgeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCB_DodgeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACB_BaseCharacter* CBCharacter = CastChecked<ACB_BaseCharacter>(ActorInfo->AvatarActor.Get());

	UAbilityTask_PlayMontageAndWait* PlayDodgeTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("PlayDodge"), CBCharacter->GetDodgeMontage());
	PlayDodgeTask->OnCompleted.AddDynamic(this, &UCB_DodgeAbility::OnCompleteCallback);
	PlayDodgeTask->ReadyForActivation();
}

void UCB_DodgeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UCB_DodgeAbility::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);

}
