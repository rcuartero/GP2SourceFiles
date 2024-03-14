// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Telekinetic.h"
#include "CatchThis/CatchThisGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CatchThis/Public/Player/Interactable.h"
#include "CatchThis/Public/Player/Damageable.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class CATCHTHIS_API APlayerCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movement Functions

	UFUNCTION()
	void MoveForward(float Value);
	
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	// Telekinetic Functions

	UFUNCTION()
	void LeftHandActivate();

	UFUNCTION()
	void RightHandActivate();

	UFUNCTION()
	void HandActivate(bool isLeftHand);

	UFUNCTION()
	void LeftHandDeactivate();

	UFUNCTION()
	void RightHandDeactivate();

	UFUNCTION()
	float GetAngleTowards(FVector object);

	UFUNCTION()
	void ManageTelekinesis();


	// Telekinetic Components
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* physicsHandleLeft;

	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* physicsHandleRight;


	// Hold Range Change Functions

	UFUNCTION()
	void IncreaseHoldRange();

	UFUNCTION()
	void DecreaseHoldRange();

	UFUNCTION()
	void StopHoldRangeChange();


	UFUNCTION()
	void Interact();


	UFUNCTION()
	virtual void TakeDamage(float damage);



public:
	// Properties
	UPROPERTY(EditAnywhere)
	float telekinesisRange;

	UPROPERTY(EditAnywhere)
	float telekinesisAngle;

	UPROPERTY(EditAnywhere)
	float interactRange;

	UPROPERTY(EditAnywhere)
	FVector handOffset;

	UPROPERTY(EditAnywhere)
	float health;

	UPROPERTY(EditAnywhere)
	float maxHealth = 100;

	UPROPERTY(EditAnywhere)
	float maxHoldRange = 100;

	UPROPERTY(EditAnywhere)
	float holdRange = 0;

	UPROPERTY(EditAnywhere)
	float holdRangeChangeRate = 5;

	bool isChangingRange = false;

private:
	AActor* leftCaughtItem;
	AActor* rightCaughtItem;
};