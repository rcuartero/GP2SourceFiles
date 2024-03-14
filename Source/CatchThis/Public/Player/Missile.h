// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "CatchThis/Public/Player/Telekinetic.h"
#include "CatchThis/Public/Player/Damageable.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Missile.generated.h"

UCLASS(Blueprintable, Category = "Projectile")
class CATCHTHIS_API AMissile : public AActor, public ITelekinetic
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void CheckExplode();

	void FireDirection(const FVector& ShootDirection);

	// Variables
	UPROPERTY(EditAnywhere)
	float speed = 1600.0f;

	UPROPERTY(EditAnywhere)
	float damage = 10;

	UPROPERTY(EditAnywhere)
	float explosionRadius = 1000.0f;

	virtual void Caught() override;

	virtual void Released() override;
};
