#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "DamageInterface.h"
#include "GameFramework/Character.h"
#include "GGBaseCharacter.generated.h"

class UCharacterAttributeSet;
class UGameplayEffect;
struct FInputActionValue;
struct FOnAttributeChangeData;

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IDamageInterface
{
    GENERATED_BODY()

public:
    AGGBaseCharacter();

public:
    /** Abilities */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Ability")
    UAbilitySystemComponent* AbilitySystem = nullptr;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Ability")
    class UCharacterAttributeSet* CharacterAttributes;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Ability")
    TSubclassOf<class UGameplayEffect> StartingAttributesEffectClass;

    /** Attack */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta=(AllowPrivateAccess="true"))
    class UGGAttackComponent* AttackComponent;

    /** Target */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
    TSubclassOf<class UGGBaseTargetComponent> TargetComponentType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
    TObjectPtr<class UGGBaseTargetComponent> TargetComponent;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    //TObjectPtr<class UGGTokenSystemComponent> TokenSystem;

protected:
    /** Overrides */
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    
    /** Event Responses */
    void OnMovementSpeedChanged(const FOnAttributeChangeData& Data) const;
    virtual void OnHealthDroppedToZero(const FOnAttributeChangeData& Data) {/** Nothing to do here */}
    
public:
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };

    UFUNCTION(BlueprintCallable, Category = "Attack")
    UGGAttackComponent* GetAttackComponent() const { return AttackComponent; }
    UFUNCTION(BlueprintCallable, Category = "Health")
    virtual bool HasHealthDroppedToZero() const { return false; }
};
