#include "Components/GGEnemyTargetComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AActor* UGGEnemyTargetComponent::GetPlayerPawn() const
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			return PC->GetPawn();
		}
	}
	return nullptr;
}

bool UGGEnemyTargetComponent::IsValidCandidate(AActor* Candidate) const
{
	// Only accept the local player pawn as a candidate
	return Candidate && Candidate == GetPlayerPawn();
}

AActor* UGGEnemyTargetComponent::SelectBestTarget()
{
	// If player is inside overlap candidates, target them; otherwise null
	AActor* Player = GetPlayerPawn();
	if (!Player) return nullptr;

	for (const TWeakObjectPtr<AActor>& C : Candidates)
	{
		if (C.Get() == Player)
			return Player;
	}
	return nullptr;
}
