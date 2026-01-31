#include "Components/GGBaseTargetComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"

UGGBaseTargetComponent::UGGBaseTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TargetDetectionSphere"));
	DetectionSphere->SetSphereRadius(Range);
	DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DetectionSphere->SetGenerateOverlapEvents(true);
}

void UGGBaseTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	DetectionSphere->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	DetectionSphere->RegisterComponent();

	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &UGGBaseTargetComponent::OnSphereBeginOverlap);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &UGGBaseTargetComponent::OnSphereEndOverlap);

	DetectionSphere->SetSphereRadius(Range);
}

void UGGBaseTargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (DetectionSphere)
	{
		DetectionSphere->OnComponentBeginOverlap.RemoveAll(this);
		DetectionSphere->OnComponentEndOverlap.RemoveAll(this);
	}
    
	Super::EndPlay(EndPlayReason);
}

AActor* UGGBaseTargetComponent::GetRandomTarget() const
{
	TArray<AActor*> Valid;
	Valid.Reserve(Candidates.Num());

	for (const TWeakObjectPtr<AActor>& C : Candidates)
	{
		if (AActor* A = C.Get())
		{
			Valid.Add(A);
		}
	}

	return Valid.Num() > 0 ? Valid[FMath::RandRange(0, Valid.Num() - 1)] : nullptr;
}

void UGGBaseTargetComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                               bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetOwner())
		return;

	if (!IsValidCandidate(OtherActor))
		return;

	Candidates.AddUnique(OtherActor);
}

void UGGBaseTargetComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;

	Candidates.RemoveAll([OtherActor](const TWeakObjectPtr<AActor>& Ptr)
	{
		return Ptr.Get() == OtherActor;
	});

	if (CurrentTarget.Get() == OtherActor)
	{
		SetCurrentTarget(nullptr);
	}
}

void UGGBaseTargetComponent::SetCurrentTarget(AActor* NewTarget)
{
	AActor* Old = CurrentTarget.Get();
	if (Old == NewTarget)
		return;

	CurrentTarget = NewTarget;
	OnTargetChanged.Broadcast(Old, NewTarget);
}

void UGGBaseTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bTickSelectTarget)
		return;

	// Clean dead candidates
	Candidates.RemoveAll([](const TWeakObjectPtr<AActor>& Ptr) { return !Ptr.IsValid(); });

	AActor* Best = SelectBestTarget();
	SetCurrentTarget(Best);
}
