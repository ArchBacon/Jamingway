#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GGAttackComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JAMINGWAYGAMEPLAY_API UGGAttackComponent : public UActorComponent
{
    GENERATED_BODY()

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
};