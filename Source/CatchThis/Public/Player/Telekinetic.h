// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Telekinetic.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, Category = "Item property")
class UTelekinetic : public UInterface
{
	GENERATED_BODY()
};

class ITelekinetic
{
	GENERATED_BODY()

public:
	virtual void Caught() = 0;

	virtual void Released() = 0;

	// Variables
    bool isCaught;
};
