#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GGAttackComponent.generated.h"

UCLASS(BlueprintType)
class JAMINGWAYGAMEPLAY_API UAnimComboSet : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Display)
    TArray<TObjectPtr<UAnimMontage>> Montages = {};
};

USTRUCT(BlueprintType)
struct FAttackResult
{
    GENERATED_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    bool AttackWasSuccessful;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    bool AttackWasSaved;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    float AttackMontageDuration;
};

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JAMINGWAYGAMEPLAY_API UGGAttackComponent : public UActorComponent
{
    GENERATED_BODY()

    UPROPERTY()
    bool bSaveAttack = false;
    UPROPERTY()
    bool bIsAttacking = false;
    UPROPERTY()
    int AttackCount = 0;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Ability)
    UAnimComboSet* AnimComboSet = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    int32 AttackTokensToReserve = 1;

public:
    //UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat|Notifies")
    //FAttackResult AttackStart(AActor* AttackTarget);
    //virtual FAttackResult AttackStart_Implementation(AActor* AttackTarget);
    //UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat|Notifies")
    //FAttackResult AttackEnd(AActor* AttackTarget);
    //virtual FAttackResult AttackEnd_Implementation(AActor* AttackTarget);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent , Category="Combat|Notifies")
    FAttackResult Attack(AActor* AttackTarget);
    virtual FAttackResult Attack_Implementation(AActor* AttackTarget);

    UFUNCTION(BlueprintCallable, Category="Combat|Notifies")
    void Reset();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat|Notifies")
    void OnComboAttackSaveNotify();
    virtual void OnComboAttackSaveNotify_Implementation();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat|Notifies")
    void OnResetComboNotify();
    virtual void OnResetComboNotify_Implementation();

private:
    UFUNCTION()
    TOptional<float> PlayMontage(int MontageIndex) const;

    UFUNCTION()
    TOptional<float> PlayNextMontage();
};