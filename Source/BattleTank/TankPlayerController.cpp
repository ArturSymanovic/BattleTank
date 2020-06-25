// Copyright Artur Symanovic 2020

#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensureMsgf(AimingComponent, TEXT("Aiming component not found")))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; }
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensureMsgf(AimingComponent, TEXT("Aiming component not found")))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)
{
	//Getting screen location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);	
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY);

	//De projection
	FVector AimingDirection;
	FVector AimingLocation; //discarded
	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		AimingLocation,
		AimingDirection
	);
	
	//Line Tracing
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = AimingDirection * AimingRange;
	FCollisionQueryParams Parameters = FCollisionQueryParams(
		FName(),
		false,
		GetPawn()
	);
	bool IsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LineTraceStart,
		LineTraceEnd,
		ECC_Visibility,
		Parameters,
		FCollisionResponseParams::DefaultResponseParam
	);

	HitLocation = FVector(0.f);

	//Parsing Results
	if (IsHit)
	{
		HitLocation = HitResult.Location;
	}
	return IsHit;
}
