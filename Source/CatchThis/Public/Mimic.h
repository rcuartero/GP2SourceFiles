// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "CatchThis/CatchThisGameModeBase.h"
#include "CatchThis/Public/Player/Interactable.h"
#include "Mimic.generated.h"

UCLASS()
class CATCHTHIS_API AMimic : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMimic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* collisionComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* itemSpawnPoint;

	UPROPERTY(EditAnywhere)
	bool isOpen = false;

	virtual void OnInteract() override;
};
