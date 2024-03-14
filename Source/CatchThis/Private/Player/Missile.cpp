// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Missile.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = speed;
		ProjectileMovementComponent->MaxSpeed = speed;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!CollisionComponent)
	{
		// Creates the capsule component
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
		RootComponent = CollisionComponent;
	}
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
		CollisionComponent->OnComponentHit.AddDynamic(this, &AMissile::Hit);
}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMissile::FireDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AMissile::Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CheckExplode();
}

void AMissile::CheckExplode()
{
	if (isCaught) return;

	// Need to add small amount at end position to start a sweep
	const FVector Start = GetRootComponent()->GetComponentLocation();
	const FVector End = GetRootComponent()->GetComponentLocation() + GetActorForwardVector().Normalize();

	// Create array to ignore owner
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());

	// Output  hit array
	TArray<FHitResult> hitArray;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, explosionRadius, UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hitArray, true, FLinearColor::Red, FLinearColor::Blue, 1.0f);

	if (Hit)
	{
		for (FHitResult hit : hitArray)
		{
			IDamageable* damageable = Cast<IDamageable>(hit.GetActor());

			if (!damageable) continue;

			damageable->TakeDamage(damage);
		}
	}

	Destroy();
}

void AMissile::Caught()
{
	isCaught = true;
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * 0;
	CollisionComponent->SetSimulatePhysics(true);
}

void AMissile::Released()
{
	isCaught = false;
	CollisionComponent->SetSimulatePhysics(false);
	FireDirection(GetActorForwardVector());
}