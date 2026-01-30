#include "Enemy/GGEnemyController.h"
#include "Enemy/GGEnemyCharacter.h"

void AGGEnemyController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    m_EnemyCharacter = Cast<AGGEnemyCharacter>(InPawn);
}