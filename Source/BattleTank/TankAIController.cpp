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
	if (!ensureMsgf(PlayerTank, TEXT("%s: Player tank not found"), *GetName())) { return; }

	auto PathResult = MoveToActor(
		PlayerTank,
		AcceptanceRadius,
		true,
		true,
		false,
		0,
		true
	);

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}
