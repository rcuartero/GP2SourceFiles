// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchThis/Public/Player/Telekinetic.h"
#include "Components/BoxComponent.h"
#include "Items.generated.h"

UCLASS()
class CATCHTHIS_API AItems : public AActor, public ITelekinetic
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* collisionComponent;


	// Inherited via ITelekinetic
	void Caught() override;

	void Released() override;

};
