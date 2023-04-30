// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
class AActor;

UENUM(BlueprintType)
enum  class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditInstanceOnly, Category = "Components")
	bool bEnableWaypoints;

	UPROPERTY(EditInstanceOnly, Category = "Components")
		AActor* Waypoint1;

	UPROPERTY(EditInstanceOnly, Category = "Components")
		AActor* Waypoint2;

	AActor* CurrentWaypoint;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	void ResetOrientation();

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	void MoveGuard();

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

	UFUNCTION()
		void OnRep_GuardState();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
