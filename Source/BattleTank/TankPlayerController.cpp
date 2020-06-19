// Copyright Artur Symanovic 2020

#include <CollisionQueryParams.h>
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tank Player Controller does not control a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!ControlledTank) { return; }
	FVector HitLocation;
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
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

	//Parsing Results
	if (IsHit)
	{
		HitLocation = HitResult.Location;
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());	
		UE_LOG(LogTemp, Warning, TEXT("Hit at: %s"), *HitResult.Location.ToString());
	}
	HitLocation = FVector(0.f);
	return IsHit;
}
