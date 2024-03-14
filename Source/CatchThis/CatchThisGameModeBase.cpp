// Fill out your copyright notice in the Description page of Project Settings.


#include "CatchThisGameModeBase.h"

void ACatchThisGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	ChangeMenuWidget(UserWidgetPrefab);

	itemManager = GetWorld()->SpawnActor<AItemManager>(itemManagerPF);
}

void ACatchThisGameModeBase::AddMimic()
{
	mimicCounter++;
}

void ACatchThisGameModeBase::RelaySpawnItem(FVector spawnLocation)
{
	if (mimicCounter > 0)
	{
		itemManager->SpawnItem(spawnLocation, mimicCounter);
		mimicCounter--;
	}
}

void ACatchThisGameModeBase::ChangeMenuWidget(TSubclassOf<UCatchThisUserWidget> newWidgetClass)
{
	if (currentWidget != nullptr)
	{
		currentWidget->RemoveFromParent();
		currentWidget = nullptr;
	}

	if (newWidgetClass != nullptr)
	{
		currentWidget = CreateWidget<UCatchThisUserWidget>(GetWorld(), newWidgetClass);
		currentWidget->AddToViewport();
	}
}
