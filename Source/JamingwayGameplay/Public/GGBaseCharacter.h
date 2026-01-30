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

    /** Abilities */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Ability, meta=(AllowPrivateAccess="true"))
    UAbilitySystemComponent* AbilitySystem = nullptr;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Ability, meta=(AllowPrivateAccess="true"))
    class UCharacterAttributeSet* CharacterAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Ability, meta=(AllowPrivateAccess="true"))
    TSubclassOf<class UGameplayEffect> StartingAttributesEffectClass;

public:
    AGGBaseCharacter();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<class UGGAttackComponent> AttackComponentType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
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
