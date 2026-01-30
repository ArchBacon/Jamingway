#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GGBaseCharacter.generated.h"

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AGGBaseCharacter();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<class UGGAttackComponent> AttackComponentType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<class UGGAttackComponent> AttackComponent;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
