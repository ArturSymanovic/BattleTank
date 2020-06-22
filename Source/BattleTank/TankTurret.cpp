// Copyright Artur Symanovic 2020


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;
	//auto Rotation = FMath::Clamp<float>(RawNewRotation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));
	//UE_LOG(LogTemp, Warning, TEXT("%s: GetRelativeRotation().Yaw: %f"), *GetOwner()->GetName(), GetRelativeRotation().Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("%s: NewYaw: %f"), *GetOwner()->GetName(), RawNewRotation);
}
