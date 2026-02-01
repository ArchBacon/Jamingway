#include "Components/GGAttackComponent.h"

#include "GGBaseCharacter.h"
#include "Log.h"
#include "Components/GGBaseTargetComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UGGAttackComponent::OnComboAttackSaveNotify_Implementation()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("ComboAttackSaveNotify"));

    if (bSaveAttack)
    {
        bSaveAttack = false;
        PlayNextMontage();
    }
}

void UGGAttackComponent::OnResetComboNotify_Implementation()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("ResetComboNotify"));

    AttackCount = 0;
    bSaveAttack = false;
    bIsAttacking = false;
}

void UGGAttackComponent::Attack_Implementation()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("Attack"));

    if (const auto Character = Cast<AGGBaseCharacter>(GetOwner()))
    {
        if (const auto Target = Character->TargetComponent->GetCurrentTarget())
        {
            auto TargetLoc = Target->GetActorLocation();
            auto MeLoc = Character->GetActorLocation();
            auto lookatme = UKismetMathLibrary::FindLookAtRotation(MeLoc, TargetLoc);
            Character->SetActorRotation(lookatme);
        }
    }

    if (bIsAttacking)
    {
        bSaveAttack = true;
        return;
    }

    bIsAttacking = true;
    PlayNextMontage();
}

void UGGAttackComponent::Reset()
{
    OnResetComboNotify();
}

void UGGAttackComponent::PlayMontage(const int MontageIndex) const
{
    if (AnimComboSet->Montages.Num() == 0)
    {
        UE_LOG(LogJamingwayGameplay, Error, TEXT("Animation Combo Sets need at least 1 animation."));
        return;
    }

    const int Index = MontageIndex % AnimComboSet->Montages.Num();
    const TObjectPtr<UAnimMontage> Montage = AnimComboSet->Montages[Index];
    const auto Character = Cast<AGGBaseCharacter>(GetOwner());
    if (Character && Montage)
    {
        Character->PlayAnimMontage(Montage);
    }
}

void UGGAttackComponent::PlayNextMontage()
{
    PlayMontage(AttackCount);
    AttackCount++;
}
