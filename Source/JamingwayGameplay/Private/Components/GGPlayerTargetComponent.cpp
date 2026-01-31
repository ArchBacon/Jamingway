#include "Components/GGPlayerTargetComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

TWeakObjectPtr<APlayerController> UGGPlayerTargetComponent::GetPC() const
{
	if (UWorld* World = GetWorld())
		return World->GetFirstPlayerController();
	return nullptr;
}

UCameraComponent* UGGPlayerTargetComponent::FindCamera() const
{
	// Common setup: camera component on owning character (or spring arm child)
	if (AActor* Owner = GetOwner())
	{
		return Owner->FindComponentByClass<UCameraComponent>();
	}
	return nullptr;
}

bool UGGPlayerTargetComponent::IsValidCandidate(AActor* Candidate) const
{
	if (!Candidate || Candidate == GetOwner())
		return false;

	// Replace with your own logic: interface, tag, team system, etc.
	// Unity used tag "character.enemy"
	return Candidate->ActorHasTag(TEXT("character.enemy"));
}

FVector UGGPlayerTargetComponent::ComputeIntentDirectionWorld(const FVector2D& Input, const UCameraComponent* Cam) const
{
	// Equivalent to your CameraSpace.InputToWorld(moveInput, cameraTransform)
	// Input.X = right, Input.Y = forward (typical)
	if (!Cam) return FVector::ZeroVector;

	const FVector CamForward = Cam->GetForwardVector();
	const FVector CamRight   = Cam->GetRightVector();

	FVector World = (CamRight * Input.X) + (CamForward * Input.Y);
	World.Z = 0.0f;
	return World.GetSafeNormal();
}

float UGGPlayerTargetComponent::ScreenCenterDistanceScore(AActor* Target) const
{
	TWeakObjectPtr<APlayerController> PC = GetPC();
	if (!PC.IsValid() || !Target) return 0.0f;

	FVector2D ScreenPos;
	const bool bOnScreen = PC->ProjectWorldLocationToScreen(Target->GetActorLocation(), ScreenPos, true);
	if (!bOnScreen) return 0.0f;

	int32 SX=0, SY=0;
	PC->GetViewportSize(SX, SY);
	const FVector2D Center(SX * 0.5f, SY * 0.5f);

	const float Dist = FVector2D::Distance(ScreenPos, Center);
	// Unity used: 1 / (1 + dist)
	return (1.0f / (1.0f + Dist)) * DistanceFromScreenCenterWeight;
}

AActor* UGGPlayerTargetComponent::SelectBestTarget()
{
	if (Candidates.Num() == 0)
		return nullptr;

	AActor* Owner = GetOwner();
	if (!Owner) return nullptr;

	// --- Intent setup (camera-relative input direction) ---
	const float InputMag = FMath::Clamp(MoveInput.Size(), 0.0f, 1.0f);
	const float IntentInfluence = FMath::GetMappedRangeValueClamped(
		FVector2D(InputDeadzone, 1.0f),
		FVector2D(0.0f, 1.0f),
		InputMag
	);

	UCameraComponent* Cam = FindCamera();
	const FVector IntentDir = (IntentInfluence > 0.0f) ? ComputeIntentDirectionWorld(MoveInput, Cam) : FVector::ZeroVector;

	// Flattened player forward
	FVector PlayerForward = Owner->GetActorForwardVector();
	PlayerForward.Z = 0.0f;
	PlayerForward = PlayerForward.GetSafeNormal();

	float BestScore = -FLT_MAX;
	AActor* BestTarget = nullptr;

	for (const TWeakObjectPtr<AActor>& Ptr : Candidates)
	{
		AActor* Target = Ptr.Get();
		if (!IsValidCandidate(Target)) continue;

		FVector ToTarget = Target->GetActorLocation() - Owner->GetActorLocation();
		ToTarget.Z = 0.0f;

		const float DistToTarget = ToTarget.Size();
		const FVector ToTargetDir = (DistToTarget > KINDA_SMALL_NUMBER) ? (ToTarget / DistToTarget) : FVector::ZeroVector;

		// distance to target score
		const float DistScore = (1.0f / (1.0f + DistToTarget)) * DistanceToTargetWeight;

		// screen center score
		const float ScreenScore = ScreenCenterDistanceScore(Target);

		// player intent score (dominant when input exists)
		float IntentScore = 0.0f;
		if (IntentInfluence > 0.0f && !IntentDir.IsNearlyZero())
		{
			IntentScore = FMath::Max(0.0f, FVector::DotProduct(IntentDir, ToTargetDir)); // [0..1]
		}
		const float IntentWeighted = IntentScore * PlayerInputDirectionWeight * IntentInfluence;

		// face direction score (dominant when no input, still tie-break when input exists)
		const float FaceScore = FMath::Max(0.0f, FVector::DotProduct(PlayerForward, ToTargetDir)); // [0..1]
		const float FaceWeightScaled = FMath::Lerp(PlayerFaceDirectionWeight, PlayerFaceDirectionWeight * 0.25f, IntentInfluence);
		const float FaceWeighted = FaceScore * FaceWeightScaled;

		const float Score = DistScore + ScreenScore + IntentWeighted + FaceWeighted;

		if (Score > BestScore)
		{
			BestScore = Score;
			BestTarget = Target;
		}
	}

	return BestTarget;
}
