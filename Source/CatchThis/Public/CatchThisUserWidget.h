// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CatchThisUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CATCHTHIS_API UCatchThisUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

	UFUNCTION()
	void SetHealthBar(float percentage);
};
