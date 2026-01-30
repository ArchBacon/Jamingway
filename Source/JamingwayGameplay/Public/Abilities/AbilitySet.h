// Copyright (c) 2025, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySet.generated.h"

class UGGGameplayAbility;

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Ability)
	TSubclassOf<UGGGameplayAbility> GrantedAbility = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Ability)
	int32 AbilityLevel = 1;
};

UCLASS(BlueprintType)
class JAMINGWAYGAMEPLAY_API UAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Display)
	TArray<FAbilityData> Abilities = {};
};
