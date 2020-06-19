// Copyright Artur Symanovic 2020


#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//Barrel = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	/*if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found."))
	*/
}
	


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	UE_LOG(
		LogTemp,
		Warning, 
		TEXT("%s aiming at %s from %s"),
		*GetOwner()->GetName(),
		*HitLocation.ToString(),
		*Barrel->GetComponentLocation().ToString()
	);
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

