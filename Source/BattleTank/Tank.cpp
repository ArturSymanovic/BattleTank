// Copyright Artur Symanovic 2020

#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	
}

void ATank::AimAt(FVector HitLocation)
{
	auto AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!ensureMsgf(AimingComponent, TEXT("%s: Aiming component is not found"), *GetName())) { return; }
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	auto Barrel = FindComponentByClass<UTankBarrel>();
	if (!ensureMsgf(Barrel, TEXT("%s: Barrel not found"), *GetName())) { return; }

	auto AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (!ensureMsgf(AimingComponent, TEXT("%s: Aiming Component not found"), *GetName())) { return; }
	
	if (!IsReloaded)
	{

		return;
	}

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
	);
	Projectile->LaunchProjectile(LaunchSpeed);
	AimingComponent->FiringState = EFiringState::Reloading;
	LastFireTime = FPlatformTime::Seconds();
}

UTankAimingComponent* ATank::GetTankAimingComponent()
{
	return FindComponentByClass<UTankAimingComponent>();
}

