#pragma once

#include "CoreMinimal.h"
#include "GGBaseTargetComponent.h"
#include "GGPlayerTargetComponent.generated.h"

class UCameraComponent;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class JAMINGWAYGAMEPLAY_API UGGPlayerTargetComponent : public UGGBaseTargetComponent
{
	GENERATED_BODY()

public:
	// Call this from your PlayerController input handling
	UFUNCTION(BlueprintCallable, Category="Targeting|Input")
	void SetMoveInput(const FVector2D& InMoveInput) { MoveInput = InMoveInput; }

protected:
	virtual bool IsValidCandidate(AActor* Candidate) const override;
	virtual AActor* SelectBestTarget() override;

	UPROPERTY(EditAnywhere, Category="Targeting|Weights")
	float PlayerInputDirectionWeight = 3.0f;

	UPROPERTY(EditAnywhere, Category="Targeting|Weights")
	float DistanceFromScreenCenterWeight = 1.5f;

	UPROPERTY(EditAnywhere, Category="Targeting|Weights")
	float PlayerFaceDirectionWeight = 1.0f;

	UPROPERTY(EditAnywhere, Category="Targeting|Weights")
	float DistanceToTargetWeight = 0.75f;

	UPROPERTY(EditAnywhere, Category="Targeting|Input")
	float InputDeadzone = 0.15f;

private:
	TWeakObjectPtr<APlayerController> GetPC() const;
	UCameraComponent* FindCamera() const;

	float ScreenCenterDistanceScore(AActor* Target) const;
	FVector ComputeIntentDirectionWorld(const FVector2D& Input, const UCameraComponent* Cam) const;

private:
	FVector2D MoveInput = FVector2D::ZeroVector;
};
