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
	if (!AimingComponent) return;
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	auto Barrel = FindComponentByClass<UTankBarrel>();
	if (!Barrel) { return; }
	if (!IsReloaded)
	{
		//TODO Show Reload Animation
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
	);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

UTankAimingComponent* ATank::GetTankAimingComponent()
{
	return FindComponentByClass<UTankAimingComponent>();
}

