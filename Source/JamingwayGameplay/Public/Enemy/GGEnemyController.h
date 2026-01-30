#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "GGEnemyController.generated.h"

UCLASS()
class JAMINGWAYGAMEPLAY_API AGGEnemyController : public AAIController
{
    GENERATED_BODY()

protected:
    void OnPossess(APawn* InPawn) override;

private:
    class AGGEnemyCharacter* m_EnemyCharacter;
};