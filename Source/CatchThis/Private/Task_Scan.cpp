// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Scan.h"

EBTNodeResult::Type UTask_Scan::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("SCANNING"));

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>((UGameplayStatics::GetPlayerPawn(GetWorld(), 0)));

	if (NavArea)
	{
		NavArea->K2_GetRandomLocationInNavigableRadius(GetWorld(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), RandomLocation, 2000.0f);
	}

	else
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Scan"), RandomLocation);

	return EBTNodeResult::Succeeded;
}