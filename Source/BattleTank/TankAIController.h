// Copyright Artur Symanovic 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 8000.f;


	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

};
