// Copyright (c) 2025, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GGGameplayAbility.generated.h"

UCLASS()
class JAMINGWAYGAMEPLAY_API UGGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Cooldown)
	FScalableFloat CooldownDuration = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Cooldown)
	FGameplayTagContainer CooldownTags = {};

	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags = {};

	virtual const FGameplayTagContainer* GetCooldownTags() const override;

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
};
