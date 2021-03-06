// Copyright Artur Symanovic 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendMoveBackward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnLeft(float Throw);

	UFUNCTION(BlueprintCallable)
	void InitialiseTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;


};
