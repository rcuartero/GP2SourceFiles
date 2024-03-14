// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerCharacter.h"
#include "Player/Missile.h"
#include "Player/Damageable.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.generated.h"

UCLASS()
class CATCHTHIS_API ATurret : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AMissile> missile;

private:
	APlayerCharacter* player;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// States
	bool isAlerted = false;
	bool isAttacking = false;
	bool isResetting = false;
	bool isStunned = false;

	// Attack Properties
	float attackTimer = 0;

	UPROPERTY(EditAnywhere)
	float attackSpeed = 5;

	UPROPERTY(EditAnywhere)
	float alertRadius = 400;

	UPROPERTY(EditAnywhere)
	float alertAngle = 30;

	UPROPERTY(EditAnywhere)
	float leashRadius = 800;

	UPROPERTY(EditAnywhere)
	float muzzleOffset;

	// Scan Properties

	UPROPERTY(EditAnywhere)
	float scanAngle = 60;

	UPROPERTY(EditAnywhere)
	float scanSpeed = 3;

	// Reset properties

	float resetTimer;

	UPROPERTY(EditAnywhere)
	float resetSpeed = 3;

	FRotator startRotation;
	FRotator stateRotation;


	// Stunned properties
	float stunTimer = 0;

	UPROPERTY(EditAnywhere)
	float stunDuration = 4;

	// functions

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UFUNCTION()
	float GetAngleTowards(FVector object);

	// Behaviors

	UFUNCTION()
	void AlertBehavior();

	UFUNCTION()
	void ScanBehavior();

	UFUNCTION()
	void ResetBehavior();

	UFUNCTION()
	void StunBehavior();

	UFUNCTION()
	virtual void TakeDamage(float damage);
};
