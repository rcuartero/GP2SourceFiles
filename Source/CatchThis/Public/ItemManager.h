// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchThis/Public/KeyObject.h"
#include "CatchThis/Public/Player/Telekinetic.h"
#include "ItemManager.generated.h"

UCLASS()
class CATCHTHIS_API AItemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemManager();


public:	

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AActor>> itemList;

	UPROPERTY(VisibleAnywhere)
	bool isKeySpawned = false;

	UFUNCTION()
	void SpawnItem(FVector spawnLocation, int mimicCounter);
};
