// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyObject.h"

// Sets default values
AKeyObject::AKeyObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKeyObject::BeginOverlap);
		CollisionComponent->InitSphereRadius(30.0f);
		RootComponent = CollisionComponent;
	}
}

// Called when the game starts or when spawned
void AKeyObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyObject::Caught()
{
	isCaught = true;
}

void AKeyObject::Released()
{
	isCaught = false;
}

void AKeyObject::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}