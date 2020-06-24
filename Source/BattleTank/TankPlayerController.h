// Copyright Artur Symanovic 2020

#pragma once

#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:


	UFUNCTION(BlueprintCallable)
	ATank* GetControlledTank();

public:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation);

private:
	ATank* ControlledTank;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.33333f;
	UPROPERTY(EditAnywhere)
	float AimingRange = 1000000.f;
};
