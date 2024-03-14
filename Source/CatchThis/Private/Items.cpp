// Fill out your copyright notice in the Description page of Project Settings.


#include "Items.h"

// Sets default values
AItems::AItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!collisionComponent) collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
}

// Called when the game starts or when spawned
void AItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItems::Caught()
{
	isCaught = true;
}

void AItems::Released()
{
	isCaught = false;
}

