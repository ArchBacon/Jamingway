#include "GGBaseCharacter.h"

AGGBaseCharacter::AGGBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AGGBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

}

void AGGBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}