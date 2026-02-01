#include "Enemy/GGEnemyCharacter.h"
#include "Components/GGEnemyTargetComponent.h"
#include "AttributeSets/CharacterAttributeSet.h"
#include "Log.h"

AGGEnemyCharacter::AGGEnemyCharacter()
    :bHealthDroppedToZero(false)
{
}

void AGGEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogJamingwayGameplay, Log, TEXT("Hello World from the AGGEnemyCharacter"));
}

void AGGEnemyCharacter::OnHealthDroppedToZero(const FOnAttributeChangeData& Data)
{
    if(Data.NewValue <= 0.0f)
    {
        bHealthDroppedToZero = true;   
    }
}