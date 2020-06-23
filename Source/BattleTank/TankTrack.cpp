// Copyright Artur Symanovic 2020


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle: %f"), *GetName(), Throttle);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	Cast<UPrimitiveComponent>(this)->AddForceAtLocation(ForceApplied, ForceLocation);
}
