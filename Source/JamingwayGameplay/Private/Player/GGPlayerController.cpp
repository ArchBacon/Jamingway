#include "Player/GGPlayerController.h"
#include "Player/GGPlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/LocalPlayer.h"

#include "Log.h"

namespace
{
	// Builds a flattened (Z=0) camera-relative direction in world space from a 2D stick input.
	// AxisX: stick X (right is +), AxisY: stick Y (up/forward is +).
	FVector BuildCameraRelativeDir2D(const APlayerController* PC, float AxisX, float AxisY)
	{
		if (!PC)
		{
			return FVector::ZeroVector;
		}

		FRotator CamRot = PC->GetControlRotation();
		if (PC->PlayerCameraManager)
		{
			CamRot = PC->PlayerCameraManager->GetCameraRotation();
		}

		const FVector CamForward3D = FRotationMatrix(CamRot).GetUnitAxis(EAxis::X);
		const FVector CamRight3D   = FRotationMatrix(CamRot).GetUnitAxis(EAxis::Y);

		FVector CamForward = FVector(CamForward3D.X, CamForward3D.Y, 0.0f);
		FVector CamRight   = FVector(CamRight3D.X,   CamRight3D.Y,   0.0f);

		CamForward.Normalize();
		CamRight.Normalize();

		return (CamForward * -AxisX) + (CamRight * AxisY);
	}
}

// -------------------------------------------------------------------------------------------
AGGPlayerController::AGGPlayerController()
    :bCanUseMouseAim(true)
{
	PrimaryActorTick.bCanEverTick = true;
}

// -------------------------------------------------------------------------------------------
void AGGPlayerController::BeginPlay()
{
    Super::BeginPlay();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (ensureMsgf(EnhancedInputComponent, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UOperatorEnhancedInputComponent or a subclass of it.")))
    {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGGPlayerController::Move);
		EnhancedInputComponent->BindAction(StickAimAction, ETriggerEvent::Triggered, this, &AGGPlayerController::StickAim);
		EnhancedInputComponent->BindAction(MouseAimAction, ETriggerEvent::Triggered, this, &AGGPlayerController::MouseAim);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AGGPlayerController::Dash);
		EnhancedInputComponent->BindAction(LightAction, ETriggerEvent::Triggered, this, &AGGPlayerController::LightAttack);
		EnhancedInputComponent->BindAction(AoEAction, ETriggerEvent::Triggered, this, &AGGPlayerController::AoEAttack);

		UE_LOG(LogJamingwayGameplay, Log, TEXT("EnhancedInputComponent Setup"));
    }
}

void AGGPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// get the current rotation
	if (m_PlayerCharacter && !m_PlayerCharacter->HasHealthDroppedToZero() && !bGamePaused)
	{
		const FRotator OldRotation = m_PlayerCharacter->GetActorRotation();

		// are we aiming with the mouse?
		if (bUsingMouse && bCanUseMouseAim)
		{
			// get the cursor world location
			FHitResult OutHit;
			GetHitResultUnderCursorByChannel(MouseAimTraceChannel, true, OutHit);

			// find the aim rotation 
			const FRotator AimRot = UKismetMathLibrary::FindLookAtRotation(m_PlayerCharacter->GetActorLocation(), OutHit.Location);

			// save the aim angle
			AimAngle = AimRot.Yaw;

			// update the yaw, reuse the pitch and roll
			m_PlayerCharacter->SetActorRotation(FRotator(OldRotation.Pitch, AimAngle, OldRotation.Roll));

		}
		else
		{
			// use quaternion interpolation to blend between our current rotation
			// and the desired aim rotation using the shortest path
			const FRotator TargetRot = FRotator(OldRotation.Pitch, AimAngle, OldRotation.Roll);

			m_PlayerCharacter->SetActorRotation(TargetRot);
		}
	}
}

// -------------------------------------------------------------------------------------------
void AGGPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    m_PlayerCharacter = Cast<AGGPlayerCharacter>(InPawn);

    // subscribe to the pawn's OnDestroyed delegate
	InPawn->OnDestroyed.AddDynamic(this, &AGGPlayerController::OnPawnDestroyed);
}

// -------------------------------------------------------------------------------------------
void AGGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

		// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);

				UE_LOG(LogJamingwayGameplay, Log, TEXT("Adding Mapping Context"));
			}
		}
	}	
}

// -------------------------------------------------------------------------------------------
void AGGPlayerController::OnPawnDestroyed(AActor* DestroyedActor)
{
    	// find the player start
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), ActorList);

	if (ActorList.Num() > 0)
	{
		// spawn a character at the player start
		const FTransform SpawnTransform = ActorList[0]->GetActorTransform();

		if (AGGPlayerCharacter* RespawnedCharacter = GetWorld()->SpawnActor<AGGPlayerCharacter>(CharacterClass, SpawnTransform))
		{
			// possess the character
			Possess(RespawnedCharacter);
		}
	}
}

void AGGPlayerController::Move(const FInputActionValue& Value)
{
	if(m_PlayerCharacter && m_PlayerCharacter->HasHealthDroppedToZero())
	{
		return;
	}

	// save the input vector
	FVector2D InputVector = Value.Get<FVector2D>();

	// route the input
	DoMove(InputVector.X, InputVector.Y);
}

void AGGPlayerController::StickAim(const FInputActionValue& Value)
{
	if(m_PlayerCharacter && m_PlayerCharacter->HasHealthDroppedToZero())
	{
		return;
	}

	// get the input vector
	FVector2D InputVector = Value.Get<FVector2D>();

	// route the input
	DoAim(InputVector.X, InputVector.Y);
}

void AGGPlayerController::MouseAim(const FInputActionValue& Value)
{
	if(m_PlayerCharacter && m_PlayerCharacter->HasHealthDroppedToZero())
	{
		return;
	}

	// raise the mouse controls flag
	if (bCanUseMouseAim)
	{
		bUsingMouse = true;

		SetShowMouseCursor(true);
	}
}

void AGGPlayerController::Dash(const FInputActionValue& Value)
{
	if(m_PlayerCharacter && m_PlayerCharacter->HasHealthDroppedToZero())
	{
		return;
	}

	// route the input
	DoDash();
}

void AGGPlayerController::LightAttack(const FInputActionValue& Value)
{
	if(m_PlayerCharacter && m_PlayerCharacter->HasHealthDroppedToZero())
	{
		return;
	}

	// route the input
	DoLightAttack();
}

void AGGPlayerController::AoEAttack(const FInputActionValue& Value)
{
	// route the input
	DoAoEAttack();
}

void AGGPlayerController::DoMove(float AxisX, float AxisY)
{
	// save the input
	LastMoveInput.X = AxisX;
	LastMoveInput.Y = AxisY;

	m_PlayerCharacter->PerformMove(AxisX, AxisY);
}

void AGGPlayerController::DoAim(float AxisX, float AxisY)
{
	// calculate the aim angle from the inputs
	AimAngle = FMath::RadiansToDegrees(FMath::Atan2(AxisY, -AxisX));

	// Convert stick input to a camera-relative world direction.
	const FVector AimDir = BuildCameraRelativeDir2D(this, AxisX, AxisY);

	// Small deadzone: ignore tiny stick noise so we don't constantly jitter the aim.
	constexpr float Deadzone = 0.15f;
	if (AimDir.SizeSquared2D() > (Deadzone * Deadzone))
	{
		// Store yaw in world space, aligned to the camera.
		AimAngle = AimDir.Rotation().Yaw;
	}

	// lower the mouse controls flag
	bUsingMouse = false;

	// hide the mouse cursor
	SetShowMouseCursor(false);
}

void AGGPlayerController::DoDash()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("Do Dash"));
}

void AGGPlayerController::DoLightAttack()
{
	m_PlayerCharacter->PerformLightAttack();
}

void AGGPlayerController::DoAoEAttack()
{
    UE_LOG(LogJamingwayGameplay, Log, TEXT("Do AoE Attack"));
}