#include "Enemy/GGEnemyCharacter.h"
#include "Log.h"

void AGGEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogJamingwayGameplay, Log, TEXT("Hello World from the AGGEnemyCharacter"));
}