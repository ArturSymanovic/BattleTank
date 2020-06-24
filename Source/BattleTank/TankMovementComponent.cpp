// Copyright Artur Symanovic 2020

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving forward"));
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving backward: %f"), Throw);
	LeftTrack->SetThrottle(-1 * Throw);
	RightTrack->SetThrottle(-1 * Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-1 * Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-1 * Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as we are overriding the behavior
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).GetSafeNormal().Z;
	IntendTurnRight(RightThrow);


	//UE_LOG(
	//	LogTemp,
	//	Warning,
	//	TEXT("%s vectoring to: %s"),
	//	*GetOwner()->GetName(),
	//	*MoveVelocity->GetSafeNormal().ToString()
	//);
}
