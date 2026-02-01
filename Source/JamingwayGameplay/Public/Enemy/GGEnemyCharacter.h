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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    bool bHealthDroppedToZero;

public:
    void OnHealthDroppedToZero(const FOnAttributeChangeData& Data) override;

public:
    bool HasHealthDroppedToZero() const override { return bHealthDroppedToZero; }

public:
    void BeginPlay() override;
};