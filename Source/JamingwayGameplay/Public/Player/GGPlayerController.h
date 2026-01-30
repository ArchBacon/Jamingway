#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "GGPlayerController.generated.h"

UCLASS()
class AGGPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    void OnPossess(APawn* InPawn) override;
    void SetupInputComponent() override;

private:
    class AGGPlayerCharacter* m_PlayerCharacter;
};