// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CatchThis/Public/Player/PlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHIS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;

	UFUNCTION()
	void OnSeePawn(APawn* PlayerPawn);

	UFUNCTION()
	void SetCanSeePlayer(bool SeePlayer, UObject* Player);

	FTimerHandle RetriggerableTimerHandle;
	FTimerDelegate FunctionDelegate;
	void RunTriggerableTimer();
};
