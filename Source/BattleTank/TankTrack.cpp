// Copyright Artur Symanovic 2020


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Cast<UPrimitiveComponent>(this)->AddForceAtLocation(ForceApplied, ForceLocation);
}
