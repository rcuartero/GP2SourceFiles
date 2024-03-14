// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Trigger Area
	triggerArea = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Area"));
	triggerArea->OnComponentBeginOverlap.AddDynamic(this, &ADoor::BeginOverlap);
	triggerArea->InitSphereRadius(20.0f);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isOpen)
	{
		SetActorLocation(GetActorLocation() + GetActorUpVector() * -openSpeed);
	}
}

void ADoor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckForKey(OtherActor);
}

void ADoor::CheckForKey(AActor* object)
{
	if (Cast<AKeyObject>(object) && !isOpen)
	{
		isOpen = true;
	}
}
