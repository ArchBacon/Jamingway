#include "GGBaseCharacter.h"
#include "Components/GGAttackComponent.h"
#include "Components/GGBaseTargetComponent.h"
#include "Abilities/GGGameplayAbility.h"
#include "AttributeSets/CharacterAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Log.h"

AGGBaseCharacter::AGGBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    // Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Configure character movement
	GetCharacterMovement()->GravityScale = 1.75f;
	GetCharacterMovement()->MaxAcceleration = 1500.f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->bUseSeparateBrakingFriction = true;
	GetCharacterMovement()->BrakingFriction = 0.0f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->GetNavMovementProperties()->bUseFixedBrakingDistanceForPaths = true;
	GetCharacterMovement()->SetFixedBrakingDistance(200.f);

	// Create attribute sets
	CharacterAttributes = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Create ability system and listen for attribute changes
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystem->AddAttributeSetSubobject(CharacterAttributes);
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetMovementSpeedAttribute()).AddUObject(this, &AGGBaseCharacter::OnMovementSpeedChanged);

	// Create Attack Component
	AttackComponent = CreateDefaultSubobject<UGGAttackComponent>(TEXT("AttackComponent"));
}

void AGGBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

	if (TargetComponentType)
	{
		TargetComponent = NewObject<UGGBaseTargetComponent>(this, TargetComponentType);

		if (TargetComponent)
		{
			TargetComponent->RegisterComponent();
		}
	}
	else
	{
		UE_LOG(LogJamingwayGameplay, Log, TEXT("Target Component Type not specified"));
	}

	if (TargetComponentType)
	{
		TargetComponent = NewObject<UGGBaseTargetComponent>(this, TargetComponentType);

		if (TargetComponent)
		{
			TargetComponent->RegisterComponent();
		}
	}
	else
	{
		UE_LOG(LogJamingwayGameplay, Log, TEXT("Target Component Type not specified"));
	}

	// Set default values to the attribute sets
	if (StartingAttributesEffectClass)
	{
		AbilitySystem->ApplyGameplayEffectToSelf(StartingAttributesEffectClass.GetDefaultObject(), 1.0f, {});
	}
	
	// Update movement speed to default attribute value
	GetCharacterMovement()->MaxWalkSpeed = AbilitySystem->GetNumericAttribute(UCharacterAttributeSet::GetMovementSpeedAttribute());
}

void AGGBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->InitAbilityActorInfo(this, this);
}

void AGGBaseCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data) const
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}