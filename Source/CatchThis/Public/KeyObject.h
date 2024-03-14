// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchThis/Public/Player/Telekinetic.h"
#include "Components/SphereComponent.h"
#include "KeyObject.generated.h"

UCLASS()
class CATCHTHIS_API AKeyObject : public AActor, public ITelekinetic
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Caught() override;

	virtual void Released() override;

	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionComponent;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
