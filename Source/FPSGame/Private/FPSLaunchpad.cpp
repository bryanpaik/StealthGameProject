// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchpad.h"
#include <FPSCharacter.h>
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AFPSLaunchpad::AFPSLaunchpad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetWorldScale3D(FVector(5.0f, 5.0f, 0.5f));
	// Set this as the parent
	RootComponent = MeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// Child of the root component which is meshcomp
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchpad::HandleOverlap);
	BoxComp->SetupAttachment(MeshComp);

	LaunchVelocity = 500;

}

void AFPSLaunchpad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr) {
		return;
	}

	FVector forward = MyPawn->GetActorForwardVector();
	FVector up = MyPawn->GetActorUpVector();
	MyPawn->LaunchCharacter(LaunchVelocity * (forward + up), 0, 0);

	UE_LOG(LogTemp, Log, TEXT("Launching player"));

	UGameplayStatics::PlaySound2D(this, LaunchPadSound);
}

