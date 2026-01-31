#include "Player/GGPlayerCharacter.h"
#include "Components/GGAttackComponent.h"
#include "Components/GGPlayerTargetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Log.h"

AGGPlayerCharacter::AGGPlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	// create the spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	SpringArm->SetRelativeRotation(FRotator(0.0f, -50.0f, 45.0f));

	SpringArm->TargetArmLength = 2000.0f;
	SpringArm->bDoCollisionTest = false;
    SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;	
    SpringArm->bEnableCameraLag = false;
    SpringArm->bEnableCameraRotationLag = false;

	// create the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(55.0f);
}

void AGGPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogJamingwayGameplay, Log, TEXT("Hello World from the AGGPlayerCharacter"));
}

void AGGPlayerCharacter::PerformMove(float AxisX, float AxisY)
{
	if (TargetComponent)
	{
        Cast<UGGPlayerTargetComponent>(TargetComponent)->SetMoveInput(FVector2D(AxisX, AxisY));
	}

	// calculate the forward component of the input
	FRotator FlatRot = GetControlRotation();
	FlatRot.Pitch = 0.0f;

    FVector CamRightVector = Camera->GetRightVector();
    FVector CamForwardVector = Camera->GetForwardVector();

	// apply the forward input
	AddMovementInput(FlatRot.RotateVector(CamForwardVector), AxisX);
	// apply the right input
	AddMovementInput(FlatRot.RotateVector(CamRightVector), AxisY);
}

void AGGPlayerCharacter::PerformLightAttack()
{
    if(AttackComponent)
    {
        AttackComponent->Attack();
    }
}