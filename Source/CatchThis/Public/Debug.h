// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchThis/Public/Player/Telekinetic.h"
#include "Debug.generated.h"

UCLASS(Blueprintable, Category = "Debug")
class CATCHTHIS_API ADebug : public AActor, public ITelekinetic
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebug();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Caught() override;

	virtual void Released() override;
};
