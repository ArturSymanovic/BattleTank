// Copyright Artur Symanovic 2020

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);


	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
	LaunchBlast->AttachTo(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	if (ensureMsgf(ProjectileMovementComponent, TEXT("Missing Projectile Movement Component!")))
	{
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovementComponent->Activate();
	}	
}

