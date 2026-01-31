#pragma once

#include "CoreMinimal.h"
#include "GGBaseCharacter.h"

#include "GGEnemyCharacter.generated.h"

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGEnemyCharacter : public AGGBaseCharacter
{
    GENERATED_BODY()
public:
    AGGEnemyCharacter();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    class UEnemyTargetComponent* TargetComponent;

public:
    void BeginPlay() override;
};