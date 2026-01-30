#pragma once

#include "CoreMinimal.h"
#include "GGBaseCharacter.h"

#include "GGPlayerCharacter.generated.h"

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGPlayerCharacter : public AGGBaseCharacter
{
    GENERATED_BODY()

protected:
    void BeginPlay() override;    
};