// Fill out your copyright notice in the Description page of Project Settings.


#include "Mimic.h"

// Sets default values
AMimic::AMimic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!collisionComponent) collisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	if (!itemSpawnPoint) itemSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Item Spawn Point"));

	RootComponent = collisionComponent;
}

// Called when the game starts or when spawned
void AMimic::BeginPlay()
{
	Super::BeginPlay();	

	ACatchThisGameModeBase* gameMode = Cast<ACatchThisGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	gameMode->AddMimic();
}

// Called every frame
void AMimic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMimic::OnInteract()
{
	if (isOpen) return;

	ACatchThisGameModeBase* gameMode = Cast<ACatchThisGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FVector spawnLocation = GetActorLocation() + itemSpawnPoint->GetComponentLocation();

	gameMode->RelaySpawnItem(spawnLocation);

	isOpen = true;
}