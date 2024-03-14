// Fill out your copyright notice in the Description page of Project Settings.

#include "CatchThisUserWidget.h"

void UCatchThisUserWidget::NativeConstruct()
{
	SetHealthBar(1.0f);
}

void UCatchThisUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}
