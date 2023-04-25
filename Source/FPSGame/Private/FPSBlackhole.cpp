// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackhole.h"
#include <Components/SphereComponent.h>

// Sets default values
AFPSBlackhole::AFPSBlackhole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Set this as the parent
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	// Child of the root component which is meshcomp
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);


	SphereComp->SetupAttachment(MeshComp);

	GravityStrength = 10000;

}

// Called when the game starts or when spawned
void AFPSBlackhole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> components;
	SphereComp->GetOverlappingComponents(components);

	for (UPrimitiveComponent* comp : components) {
		// UE_LOG(LogTemp, Warning, TEXT("Component: %s"), *FString(comp->GetName()));
		if (comp && comp->IsSimulatingPhysics()) {
			FVector dir = this->GetActorLocation() - comp->GetComponentLocation();
			comp->AddForce(dir * GravityStrength);
		}
	}
	

}

