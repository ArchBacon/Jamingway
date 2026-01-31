#include "Enemy/GGEnemyCharacter.h"
#include "Components/GGEnemyTargetComponent.h"
#include "Log.h"

AGGEnemyCharacter::AGGEnemyCharacter()
{
}

void AGGEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogJamingwayGameplay, Log, TEXT("Hello World from the AGGEnemyCharacter"));
}