#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GGTokenSystemComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UGGTokenSystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGGTokenSystemComponent();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    int32 AttackTokenCount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    int32 MaxAttackTokenCount;

    UFUNCTION(BlueprintCallable, Category="JamingwayGameplay")
    bool CanReserveAttackToken(int Amount);
    UFUNCTION(BlueprintCallable, Category="JamingwayGameplay")
    bool ReserveAttackToken(int Amount);
    UFUNCTION(BlueprintCallable, Category="JamingwayGameplay")
    void ReturnAttackToken(int Amount);
};