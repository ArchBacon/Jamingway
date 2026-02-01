#include "Components/GGAttackComponent.h"
#include "Components/GGTokenSystemComponent.h"
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

FAttackResult UGGAttackComponent::Attack_Implementation(AActor* AttackTarget)
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Attack"), *GetOwner()->GetName());

    const auto Character = Cast<AGGBaseCharacter>(GetOwner());
    if (!Character)
    {
        // Unable to attack when we are not a Character
        return {false, false, 0.0f};
    }

    if(Character->HasHealthDroppedToZero())
    {
        // Do nothing when you are dead!
        return {false, false, 0.0f};
    }

    if(AttackTarget)
    {
        UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Current attack target: %s"), *GetOwner()->GetName(), *AttackTarget->GetName());

        UGGTokenSystemComponent* TokenSystem = Cast<UGGTokenSystemComponent>(AttackTarget->FindComponentByClass(UGGTokenSystemComponent::StaticClass()));
        if(TokenSystem)
        {
            if(TokenSystem->CanReserveAttackToken(AttackTokensToReserve))
            {
                UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Start reserving tokens from: %s"), *GetOwner()->GetName(), *AttackTarget->GetName());
                TokenSystem->ReserveAttackToken(AttackTokensToReserve);
                UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Reserved tokens from: %s"), *GetOwner()->GetName(), *AttackTarget->GetName());
            }
            else
            {
                UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Unable to attack the target, no tokens left"), *GetOwner()->GetName());
                // Unable to attack the target!
                return {false, false, 0.0f};
            }
        }
        else
        {
            UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], No TokenSystem present on AttackTarget"), *GetOwner()->GetName());
        }

        auto TargetLoc = AttackTarget->GetActorLocation();
        auto MeLoc = Character->GetActorLocation();
        auto LookAtMe = UKismetMathLibrary::FindLookAtRotation(MeLoc, TargetLoc);

        Character->SetActorRotation(LookAtMe);
    }

    if (bIsAttacking)
    {
        UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Save Attack"), *GetOwner()->GetName());
        bSaveAttack = true;
        return {true, true, 0.0f};
    }

    auto result = PlayNextMontage();
    if(result)
    {
        UE_LOG(LogJamingwayGameplay, Log, TEXT("[%s], Playing next montage, %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(*result));
        bIsAttacking = true;
        return { true, false, *result };
    }

    // Dunno what happend ... 
    return {false, false, 0.0f};
}

void UGGAttackComponent::Reset()
{
    OnResetComboNotify();
}

TOptional<float> UGGAttackComponent::PlayMontage(const int MontageIndex) const
{
    if (AnimComboSet->Montages.Num() == 0)
    {
        UE_LOG(LogJamingwayGameplay, Error, TEXT("Animation Combo Sets need at least 1 animation."));
        return {};
    }

    const int Index = MontageIndex % AnimComboSet->Montages.Num();
    const TObjectPtr<UAnimMontage> Montage = AnimComboSet->Montages[Index];
    const auto Character = Cast<AGGBaseCharacter>(GetOwner());
    if (Character && Montage)
    {
        return Character->PlayAnimMontage(Montage);
    }

    return {};
}

TOptional<float> UGGAttackComponent::PlayNextMontage()
{
    auto result = PlayMontage(AttackCount);
    if(result)
    {
        AttackCount++;
    }

    return result;
}
