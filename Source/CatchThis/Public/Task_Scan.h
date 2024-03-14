// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Math/Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Task_Scan.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHIS_API UTask_Scan : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	

	FVector RandomLocation;
	UNavigationSystemV1* NavArea;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
