// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CATCHTHIS_API EnumNames
{
public:
	EnumNames();
	~EnumNames();

	UENUM()
	enum State
	{
		Scanning UMETA(DisplayName = "Scanning"),
		Attacking UMETA(DisplayName = "Attacking"),
		Resetting UMETA(DisplayName = "Resetting")
	};
};
