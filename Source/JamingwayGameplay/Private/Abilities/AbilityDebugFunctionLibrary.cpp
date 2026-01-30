// Copyright (c) 2025, Christian Delicaat. All rights reserved.

#include "Abilities/AbilityDebugFunctionLibrary.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Log.h"
#include "Logging/StructuredLog.h"

void UAbilityDebugFunctionLibrary::PrintAttribute(
	UAbilitySystemComponent* AbilitySystem,
	const FGameplayAttribute Attribute,
	const FLinearColor TextColor,
	const float Duration
) {
	if (!AbilitySystem)
	{
		UE_LOGFMT(LogJamingwayGameplay, Warning, "[AbilityDebugFunctionLibrary::PrintAttribute]: No valid ability system component.");
		return;
	}

	if (!AbilitySystem->HasAttributeSetForAttribute(Attribute))
	{
		UE_LOGFMT(LogJamingwayGameplay, Warning, "[AbilityDebugFunctionLibrary::PrintAttribute]: No attribute selected.");
		return;
	}
	const FString AttributeValue = FString::SanitizeFloat(AbilitySystem->GetNumericAttribute(Attribute), 3);

	const int Key = GetTypeHash(Attribute.GetName());
	GEngine->AddOnScreenDebugMessage(Key, Duration, TextColor.ToFColor(true), FString::Printf(TEXT("%s: %s"), *Attribute.GetName(), *AttributeValue));
}

void UAbilityDebugFunctionLibrary::PrintAllAttributes(
	UAbilitySystemComponent* AbilitySystem,
	const FLinearColor TextColor,
	const float Duration
) {
	if (!AbilitySystem)
	{
		UE_LOGFMT(LogJamingwayGameplay, Warning, "[AbilityDebugFunctionLibrary::PrintAllAttributes]: No valid ability system component.");
		return;
	}

	TArray<FGameplayAttribute> Attributes{};
	AbilitySystem->GetAllAttributes(Attributes);
	for (FGameplayAttribute Attribute : Attributes)
	{
		const FString AttributeValue = FString::SanitizeFloat(AbilitySystem->GetNumericAttribute(Attribute), 3);
		
		const int Key = GetTypeHash(Attribute.GetName());
		GEngine->AddOnScreenDebugMessage(Key, Duration, TextColor.ToFColor(true), FString::Printf(TEXT("%s: %s"), *Attribute.GetName(), *AttributeValue));
	}
}

void UAbilityDebugFunctionLibrary::PrintOwnedGameplayTags(
	UAbilitySystemComponent* AbilitySystem,
	const FLinearColor TextColor,
	const float Duration
) {
	if (!AbilitySystem)
	{
		UE_LOGFMT(LogJamingwayGameplay, Warning, "[AbilityDebugFunctionLibrary::PrintOwnedGameplayTags]: No valid ability system component.");
		return;
	}

	const auto OwnedTags = AbilitySystem->GetOwnedGameplayTags().GetGameplayTagArray();
	for (FGameplayTag Tag : OwnedTags)
	{
		const int Key = GetTypeHash(Tag.GetTagName());
		GEngine->AddOnScreenDebugMessage(Key, Duration, TextColor.ToFColor(true), Tag.GetTagName().ToString());
	}
}
