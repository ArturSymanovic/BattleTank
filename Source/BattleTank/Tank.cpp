// Copyright Artur Symanovic 2020

#include "Engine/World.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamageToApply = FMath::Clamp(FMath::RoundToInt(DamageAmount), 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("Damage Amount: %f"), DamageAmount);
	UE_LOG(LogTemp, Warning, TEXT("Damage To Apply: %i"), DamageToApply);
	CurrentHealth -= (int32)DamageToApply;
	return DamageToApply;
}

