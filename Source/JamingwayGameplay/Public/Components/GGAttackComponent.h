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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Ability, meta=(AllowPrivateAccess="true"))
    UAnimComboSet* AnimComboSet = nullptr;

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent , Category="Combat|Notifies")
    void Attack();
    virtual void Attack_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat|Notifies")
    void OnComboAttackSaveNotify();
    virtual void OnComboAttackSaveNotify_Implementation();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat|Notifies")
    void OnResetComboNotify();
    virtual void OnResetComboNotify_Implementation();

private:
    UFUNCTION()
    void PlayMontage(int MontageIndex) const;

    UFUNCTION()
    void PlayNextMontage();
};