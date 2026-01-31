#include "Components/GGAttackComponent.h"
#include "Log.h"

void UGGAttackComponent::OnComboAttackSaveNotify_Implementation()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("ComboAttackSaveNotify"));
}

void UGGAttackComponent::OnResetComboNotify_Implementation()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("ResetComboNotify"));
}

void UGGAttackComponent::Attack_Implementation()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("Attack"));
}