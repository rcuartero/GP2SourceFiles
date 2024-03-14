// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug.h"

// Sets default values
ADebug::ADebug()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebug::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADebug::Caught()
{
	isCaught = true;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("Caught the debug object"));
}

void ADebug::Released()
{
	isCaught = false;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, TEXT("Released the debug object"));
}

