// Copyright Artur Symanovic 2020

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh Component"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);


	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast Component"));
	LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast= CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast Component"));
	ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force Component"));
	ExplosionForce->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->bAutoActivate = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(
	UPrimitiveComponent* PrimitiveComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
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

