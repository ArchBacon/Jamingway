// Copyright (c) 2025, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TokenInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTokenInterface : public UInterface
{
	GENERATED_BODY()
};

class JAMINGWAYGAMEPLAY_API ITokenInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool ReserveAttackToken(int32 Amount);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ReturnAttackToken(int32 Amount);
};
