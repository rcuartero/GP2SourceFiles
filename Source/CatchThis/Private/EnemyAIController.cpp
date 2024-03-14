// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	if (!PawnSensing)
	{
		PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSSensing"));
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyAIController::OnSeePawn);
}

void AEnemyAIController::OnSeePawn(APawn* PlayerPawn)
{
	// Only see player
	APlayerCharacter* player = Cast<APlayerCharacter>(PlayerPawn);
	if (!player) return;

	SetCanSeePlayer(true, player);
}

void AEnemyAIController::SetCanSeePlayer(bool SeePlayer, UObject* Player)
{
	UBlackboardComponent* bb = GetBlackboardComponent();
	bb->SetValueAsBool(FName("Can See Player"), SeePlayer);
	if (SeePlayer) bb->SetValueAsObject(FName("Player Target"), Player);
}

void AEnemyAIController::RunTriggerableTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);
	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, GetPawn());
	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, PawnSensing->SensingInterval * 2.0f, false);
}