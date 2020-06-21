// Copyright Artur Symanovic 2020

#include "TankBarrel.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//Barrel = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}
	


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	
	if (!Barrel) { return; }

	FVector LaunchVelocity = FVector(0.f);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		5.f,
		false,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams(),
		TArray<AActor*>({ GetOwner() }),
		false
	);

	if (bHaveAimSolution)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTo(AimDirection);

		/*UE_LOG(
			LogTemp,
			Warning,
			TEXT("%s aiming at %s from %s. Calculated launch velocity: %s"),
			*GetOwner()->GetName(),
			*HitLocation.ToString(),
			*StartLocation.ToString(),
			*AimDirection.ToString()
		);*/
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("No Solution!!!!!!."))
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
/*	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel not found."))
	}*/	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTo(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("Barrel forward vector: %s"), *BarrelRotation.ToString());
	FRotator AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimDirection: %s"), *AimAsRotator.ToString());

	FRotator DeltaRotation = AimAsRotator - BarrelRotation;
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotation: %s"), *DeltaRotation.ToString());
	Barrel->Elevate(DeltaRotation.Pitch);
}

