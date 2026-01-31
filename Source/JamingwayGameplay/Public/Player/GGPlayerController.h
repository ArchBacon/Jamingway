#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "GGPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class AGGPlayerCharacter;

UCLASS()
class AGGPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
	AGGPlayerController();

    void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
    bool bCanUseMouseAim;

    /** Default input mapping contexts to add on begin play */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Movement input action */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputAction* MoveAction;
	/** Gamepad aim input action */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputAction* StickAimAction;
	/** Mouse aim input action */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputAction* MouseAimAction;
	/** Dash input action */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputAction* DashAction;
	/** Shooting input action */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputAction* LightAction;
	/** AoE attack input action */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputAction* AoEAction;

    /** Trace channel to use for mouse aim */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TEnumAsByte<ETraceTypeQuery> MouseAimTraceChannel;

	/** Character class to respawn when the possessed pawn is destroyed */
	UPROPERTY(EditAnywhere, Category = "Respawn")
	TSubclassOf<AGGPlayerCharacter> CharacterClass;

protected:
    UFUNCTION()
    void OnPawnDestroyed(AActor* DestroyedActor);

    UFUNCTION(BlueprintCallable, Category ="Input|Input Mappings")
	void DoMove(float AxisX, float AxisY);

	UFUNCTION(BlueprintCallable, Category ="Input|Input Mappings")
	void DoAim(float AxisX, float AxisY);

	UFUNCTION(BlueprintCallable, Category ="Input|Input Mappings")
	void DoDash();

	UFUNCTION(BlueprintCallable, Category ="Input|Input Mappings")
	void DoLightAttack();

	UFUNCTION(BlueprintCallable, Category ="Input|Input Mappings")
	void DoAoEAttack();

protected:
    void BeginPlay() override;
    void OnPossess(APawn* InPawn) override;
    void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);
	void StickAim(const FInputActionValue& Value);
	void MouseAim(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
	void LightAttack(const FInputActionValue& Value);
	void AoEAttack(const FInputActionValue& Value);

private:
    class AGGPlayerCharacter* m_PlayerCharacter;

	/** If true, the player is using mouse aim */
	bool bUsingMouse = false;

	/** Last held move input */
	FVector2D LastMoveInput;

	/** Aim Yaw Angle in degrees */
	float AimAngle = 0.0f;
};