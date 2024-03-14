// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CatchThis/Public/CatchThisUserWidget.h"
#include "CatchThis/Public/ItemManager.h"
#include "CatchThisGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHIS_API ACatchThisGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;

public:

	UPROPERTY(EditAnywhere)
	int mimicCounter = 0;

	UPROPERTY(EditAnywhere, Category = Prefab)
	TSubclassOf<class AItemManager> itemManagerPF;

	UPROPERTY(EditAnywhere)
	AItemManager* itemManager;

	UFUNCTION()
	void AddMimic();

	UFUNCTION()
	void RelaySpawnItem(FVector spawnLocation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UCatchThisUserWidget> UserWidgetPrefab;

	UFUNCTION(BlueprintCallable, Category = "GUI")
	void ChangeMenuWidget(TSubclassOf<UCatchThisUserWidget> newWidgetClass);

	UPROPERTY()
	UCatchThisUserWidget* currentWidget;
};
