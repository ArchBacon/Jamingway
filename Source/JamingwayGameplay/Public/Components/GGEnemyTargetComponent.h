#pragma once

#include "CoreMinimal.h"
#include "GGBaseTargetComponent.h"
#include "GGEnemyTargetComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class JAMINGWAYGAMEPLAY_API UGGEnemyTargetComponent : public UGGBaseTargetComponent
{
	GENERATED_BODY()

protected:
	virtual bool IsValidCandidate(AActor* Candidate) const override;
	virtual AActor* SelectBestTarget() override;

private:
	AActor* GetPlayerPawn() const;
};
