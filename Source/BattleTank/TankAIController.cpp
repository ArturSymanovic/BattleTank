// Copyright Artur Symanovic 2020

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn<ATank>();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn<ATank>();

	if (!PlayerTank) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Aiming"));
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}
