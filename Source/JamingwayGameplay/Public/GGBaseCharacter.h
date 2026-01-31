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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    TSubclassOf<class UGGAttackComponent> AttackComponentType;  
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    TObjectPtr<class UGGAttackComponent> AttackComponent;

protected:
    /** Overrides */
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    
    /** Event Responses */
    void OnMovementSpeedChanged(const FOnAttributeChangeData& Data) const;
    
public:
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };
};
