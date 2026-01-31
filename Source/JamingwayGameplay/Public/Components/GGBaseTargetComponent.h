#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGBaseTargetComponent.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetChanged, AActor*, OldTarget, AActor*, NewTarget);

UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class JAMINGWAYGAMEPLAY_API UGGBaseTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGGBaseTargetComponent();

	UFUNCTION(BlueprintCallable, Category="Targeting")
	AActor* GetCurrentTarget() const { return CurrentTarget.Get(); }

	UFUNCTION(BlueprintCallable, Category="Targeting")
	AActor* GetRandomTarget() const;

	UPROPERTY(BlueprintAssignable, Category="Targeting")
	FOnTargetChanged OnTargetChanged;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Derived classes define what is a valid target and how to pick it.
	virtual bool IsValidCandidate(AActor* Candidate) const PURE_VIRTUAL(UBaseTargetComponent::IsValidCandidate, return false;);
	virtual AActor* SelectBestTarget() PURE_VIRTUAL(UBaseTargetComponent::SelectBestTarget, return nullptr;);

	void SetCurrentTarget(AActor* NewTarget);

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                         const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, Category="Targeting|Range")
	float Range = 900.0f;

	UPROPERTY(EditAnywhere, Category="Targeting|Debug")
	bool bTickSelectTarget = true;

	// Overlap volume that collects candidates
	UPROPERTY(Transient)
	TObjectPtr<USphereComponent> DetectionSphere = nullptr;

	// Candidates currently inside the sphere
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<AActor>> Candidates;

	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> CurrentTarget;
};
