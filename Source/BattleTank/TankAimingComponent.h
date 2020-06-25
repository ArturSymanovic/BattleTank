// Copyright Artur Symanovic 2020

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	bool IsBarrelMoving();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	void InitialiseTurretAndBarrel(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTo();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f;

	double LastFireTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	FVector AimDirection = FVector{0.f};
};
