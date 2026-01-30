#include "GGBaseCharacter.h"
#include "Components/GGAttackComponent.h"
#include "Log.h"

AGGBaseCharacter::AGGBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true; 
}

void AGGBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (AttackComponentType)
    {
        AttackComponent = NewObject<UGGAttackComponent>(this, AttackComponentType);

        if (AttackComponent)
        {
            AttackComponent->RegisterComponent();
        }
    }
    else
    {
        UE_LOG(LogJamingwayGameplay, Log, TEXT("Attack Component Type not specified"));
    }
}

void AGGBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}