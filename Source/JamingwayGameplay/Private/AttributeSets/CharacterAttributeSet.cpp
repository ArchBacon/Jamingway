// Copyright (c) 2025, Christian Delicaat. All rights reserved.

#include "AttributeSets/CharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "DamageInterface.h"
#include "Log.h"

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// No attribute should be a negative value
	NewValue = FMath::Max<float>(NewValue, 0.0f);

	if (Attribute == GetHealthAttribute())
	{
		// Health cannot be higher than MaxHealth
		NewValue = FMath::Min<float>(NewValue, GetMaxHealth());
	}
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	void OnDamaged(AActor* SourceActor, float DamageAmount);
	void OnTargetDamaged(AActor* DamagedActor, float DamageAmount);
	void OnTargetKilled(AActor* KilledActor);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float NewHealth = GetHealth();
		const float Magnitude = Data.EvaluatedData.Magnitude;

		const auto DamageSource = Data.EffectSpec.GetContext().GetInstigator();
		const auto DamageTarget = Data.Target.GetOwner();
		
		// Is damaged?
		if (Magnitude <= 0.0f)
		{
			// Notify Source
			if (DamageSource->GetClass()->ImplementsInterface(UDamageInterface::StaticClass()))
			{
				IDamageInterface::Execute_OnDamageDealt(DamageSource, DamageTarget, FMath::Abs(Magnitude));
				UE_LOGFMT(LogJamingwayGameplay, Log, "{0} dealt {1} damage to {2}", DamageSource->GetName(), FMath::Abs(Magnitude), DamageTarget->GetName());
				
				if (NewHealth <= 0.0f)
				{
					IDamageInterface::Execute_OnKill(DamageSource, DamageTarget);
					UE_LOGFMT(LogJamingwayGameplay, Log, "{0} killed {1}", DamageSource->GetName(), DamageTarget->GetName());
				}
			}

			// Notify Target
			if (auto Target = Cast<IDamageInterface>(DamageTarget))
			{
				IDamageInterface::Execute_OnDamageTaken(DamageTarget, DamageSource, FMath::Abs(Magnitude));
				UE_LOGFMT(LogJamingwayGameplay, Log, "{0} was dealt {1} damage by {2}", DamageTarget->GetName(), FMath::Abs(Magnitude), DamageSource->GetName());

				if (NewHealth <= 0.0f)
				{
					IDamageInterface::Execute_OnDeath(DamageTarget, DamageSource);
					UE_LOGFMT(LogJamingwayGameplay, Log, "{0} was killed by {1}", DamageTarget->GetName(), DamageSource->GetName());
				}
			}
		}
	}
}
