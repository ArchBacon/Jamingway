#include "Player/GGPlayerController.h"
#include "Player/GGPlayerCharacter.h"

// -------------------------------------------------------------------------------------------
void AGGPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    m_PlayerCharacter = Cast<AGGPlayerCharacter>(InPawn);
}

// -------------------------------------------------------------------------------------------
void AGGPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();


}