#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "GGEnemyController.generated.h"

UCLASS()
class AGGEnemyController : public AAIController
{
    GENERATED_BODY()

protected:
    void OnPossess(APawn* InPawn) override;

private:
    class AGGEnemyCharacter* m_EnemyCharacter;
};