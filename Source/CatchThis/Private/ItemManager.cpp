// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

// Sets default values
AItemManager::AItemManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItemManager::SpawnItem(FVector spawnLocation, int mimicCounter)
{
	int32 index;

	if (mimicCounter == 1 && !isKeySpawned)	index = 0; // Index for Key
	
	else
	{
		if (isKeySpawned) index = FMath::RandRange(1, itemList.Num() - 1); // Randomitem excluding key
		else index = FMath::RandRange(0, itemList.Num() - 1); // Randomitem
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();

	// Can only cast onto already existing objects
	AActor* spawnItem = GetWorld()->SpawnActor<AActor>(itemList[index], spawnLocation, GetActorRotation(), spawnParams);

	if (AKeyObject* key = Cast<AKeyObject>(spawnItem)) isKeySpawned = true;
}