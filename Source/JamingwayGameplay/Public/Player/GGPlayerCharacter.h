#pragma once

#include "CoreMinimal.h"
#include "GGBaseCharacter.h"
#include "TokenInterface.h"
#include "GGPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGPlayerCharacter : public AGGBaseCharacter, public ITokenInterface
{
    GENERATED_BODY()

public:
    AGGPlayerCharacter();

public:
	/** Camera boom spring arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	/** Player Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="JamingwayGameplay")
    bool bHealthDroppedToZero;

public:
    void OnHealthDroppedToZero(const FOnAttributeChangeData& Data) override;

public:
    void PerformMove(float AxisX, float AxisY);
    void PerformLightAttack(AActor* AttackTarget);

    bool HasHealthDroppedToZero() const override { return bHealthDroppedToZero; }

protected:
    void BeginPlay() override;    
};