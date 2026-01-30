#pragma once

#include "CoreMinimal.h"
#include "GGBaseCharacter.h"

#include "GGEnemyCharacter.generated.h"

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGEnemyCharacter : public AGGBaseCharacter
{
    GENERATED_BODY()

public:
    void BeginPlay() override;
};