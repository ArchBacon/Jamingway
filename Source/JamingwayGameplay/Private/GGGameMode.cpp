#include "GGGameMode.h"

#include "Player/GGPlayerController.h"
#include "Player/GGPlayerCharacter.h"

AGGGameMode::AGGGameMode()
{
    PlayerControllerClass = AGGPlayerController::StaticClass();
    DefaultPawnClass = AGGPlayerCharacter::StaticClass();
}