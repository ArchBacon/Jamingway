#pragma once

#include "CoreMinimal.h"
#include "GGBaseCharacter.h"

#include "GGPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGPlayerCharacter : public AGGBaseCharacter
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
    /** Target System */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    class UPlayerTargetComponent* TargetComponent;

public:
    void PerformMove(float AxisX, float AxisY);
    void PerformLightAttack();

protected:
    void BeginPlay() override;    
};