// Copyright (c) 2025, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilityDebugFunctionLibrary.generated.h"

class UAbilitySystemComponent;
struct FGameplayAttribute;

UCLASS()
class JAMINGWAYGAMEPLAY_API UAbilityDebugFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Ability|Debug")
	static void PrintAttribute(UAbilitySystemComponent* AbilitySystem, FGameplayAttribute Attribute, FLinearColor TextColor = FLinearColor::Green, float Duration = 2.0f);
	
	UFUNCTION(BlueprintCallable, Category="Ability|Debug")
	static void PrintAllAttributes(UAbilitySystemComponent* AbilitySystem, FLinearColor TextColor = FLinearColor::Green, float Duration = 2.0f);

	UFUNCTION(BlueprintCallable, Category="Ability|Debug")
	static void PrintOwnedGameplayTags(UAbilitySystemComponent* AbilitySystem, FLinearColor TextColor = FLinearColor::Yellow, float Duration = 2.0f);
};
