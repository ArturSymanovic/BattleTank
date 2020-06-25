// Copyright Artur Symanovic 2020

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}
	
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::InitialiseTurretAndBarrel(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
	if (!ensureMsgf((BarrelToSet && TurretToSet), TEXT("%s: Barrel or turret not found"), *GetOwner()->GetName())) { return; }
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	
	if (!Barrel || !Turret) { return; }
	if (!ensureMsgf((Barrel && Turret), TEXT("%s: Barrel or turret not found"), *GetOwner()->GetName())) { return; }

	FVector LaunchVelocity = FVector(0.f);
	FVector StartLocation = Turret->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
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
	}
}

void UTankAimingComponent::MoveBarrelTo(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotation = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensureMsgf(Barrel, TEXT("%s: Barrel not found"), *GetName())) { return; }
	if (!ensureMsgf(ProjectileBlueprint, TEXT("%s: Projectileblueprint not found"), *GetName())) { return; }

	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!IsReloaded) { return; }

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);
	Projectile->LaunchProjectile(LaunchSpeed);
	FiringState = EFiringState::Reloading;
	LastFireTime = FPlatformTime::Seconds();
}
