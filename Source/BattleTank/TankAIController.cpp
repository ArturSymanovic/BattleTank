// Copyright Artur Symanovic 2020
#include "Tank.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	if (!ensureMsgf(ControlledTank, TEXT("%s: Controlled tank not found"), *GetName())) { return; }

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensureMsgf(PlayerTank, TEXT("%s: Player tank not found"), *GetName())) { return; }

	MoveToActor(
		PlayerTank,
		AcceptanceRadius,
		true,
		true,
		false,
		0,
		true
	);
	
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensureMsgf(AimingComponent, TEXT("%s: Aiming component not found"), *GetName())) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}

}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (!ensureMsgf(InPawn, TEXT("Pawn is null"))) { return; }
	ATank* InTank = Cast<ATank>(InPawn);
	if (!ensureMsgf(InTank, TEXT("Tank is null"))) { return; }
	InTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);

}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Successful delegate creation!"));
}
