#include "Components/GGTokenSystemComponent.h"
#include "Log.h"

UGGTokenSystemComponent::UGGTokenSystemComponent()
{
    AttackTokenCount = 1;
    MaxAttackTokenCount = 1;
}

bool UGGTokenSystemComponent::CanReserveAttackToken(int Amount)
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s][TokenSystem][CanReserveAttackToken], AttackTokenAmount: %d"), *GetOwner()->GetName(), AttackTokenCount);
    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s][TokenSystem][CanReserveAttackToken], Tokens to reserve, Amount: %d"), *GetOwner()->GetName(), Amount);
    return AttackTokenCount - Amount >= 0;
}

bool UGGTokenSystemComponent::ReserveAttackToken(int Amount)
{
    if(!CanReserveAttackToken(Amount))
    {
        return false;
    }

    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s][TokenSystem], Reserved attack tokens, Amount: %d"), *GetOwner()->GetName(), Amount);
    AttackTokenCount -= Amount;
    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s][TokenSystem], AttackTokenAmount: %d"), *GetOwner()->GetName(), AttackTokenCount);
    return true;
}


void UGGTokenSystemComponent::ReturnAttackToken(int Amount)
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s][TokenSystem], Returned attack tokens, Amount: %d"), *GetOwner()->GetName(), Amount);
    AttackTokenCount = FMath::Min(AttackTokenCount + Amount, MaxAttackTokenCount);
    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s][TokenSystem], AttackTokenAmount: %d"), *GetOwner()->GetName(), AttackTokenCount);
}
