// Copyright Artur Symanovic 2020

#pragma once

#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

public:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation);

private:
	APawn* ControlledTank;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.33333f;
	UPROPERTY(EditAnywhere)
	float AimingRange = 1000000.f;


	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};
