// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CatchThis/Public/KeyObject.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"


UCLASS()
class CATCHTHIS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void CheckForKey(AActor* object);

	// Variables
	bool isOpen = false;

	UPROPERTY(EditAnywhere)
	float openSpeed = 0.2f;

public:
	//Components
	UPROPERTY(EditAnywhere)
	USphereComponent* triggerArea;
};
