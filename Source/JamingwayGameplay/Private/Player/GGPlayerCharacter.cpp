#include "Player/GGPlayerCharacter.h"
#include "Log.h"

void AGGPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogJamingwayGameplay, Log, TEXT("Hello World from the AGGPlayerCharacter"));
}