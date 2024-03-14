// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	startRotation = GetActorRotation();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isStunned)
	{
		stunTimer += DeltaTime;
		StunBehavior();
	}

	else if (FVector::Distance(GetActorLocation(), player->GetActorLocation()) > leashRadius && isAlerted)
	{
		resetTimer += DeltaTime;
		ResetBehavior();
	}

	else if (isAlerted)
	{
		attackTimer += DeltaTime;
		AlertBehavior();
	}

	else ScanBehavior();
}

void ATurret::FireProjectile()
{

	if (missile)
	{
		TArray<AActor*> actorsToIgnore;
		actorsToIgnore.Add(GetOwner());
		FHitResult hitRay;

		// Use Line trace for precision telekinetic activation
		const bool HitLine = UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation() + (GetActorForwardVector() * muzzleOffset), player->GetActorLocation(), UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hitRay, true, FLinearColor::Red, FLinearColor::Blue, 1.0f);

		if (HitLine)
		{
			FString hitName = hitRay.GetActor()->GetName();

			APlayerCharacter* playerCheck = Cast<APlayerCharacter>(hitRay.GetActor());

			if (playerCheck)
			{
				FVector muzzleLocation = GetActorLocation();
		
				FVector directionToPlayer = player->GetActorLocation() - muzzleLocation;
				FRotator muzzleRotation = directionToPlayer.Rotation();
				muzzleRotation.Normalize();

				muzzleLocation += (muzzleRotation.Vector() * muzzleOffset);

				UWorld* world = GetWorld();

				if (world)
				{
					FActorSpawnParameters spawnParams;
					spawnParams.Owner = this;
					spawnParams.Instigator = GetInstigator();

					// spawn projectile
					AMissile* missileFired = world->SpawnActor<AMissile>(missile, muzzleLocation, muzzleRotation, spawnParams);
				}
			}
		}
	}

	stateRotation = GetActorRotation();
	attackTimer = 0;
	isAttacking = false;
}

float ATurret::GetAngleTowards(FVector angleTowards)
{
	FVector vectorToPlayer = angleTowards - GetActorLocation();
	vectorToPlayer.Normalize();

	FVector forwardVector = GetActorForwardVector();
	forwardVector.Normalize();

	float dotProduct = FVector::DotProduct(vectorToPlayer, forwardVector);
	float radians = FMath::Acos(dotProduct);
	float degrees = FMath::RadiansToDegrees(radians);

	return degrees;
}

void ATurret::AlertBehavior()
{
	if (!isAttacking)
	{
		stateRotation = GetActorRotation();
		isAttacking = true;
	}

	FVector directionToPlayer = player->GetActorLocation() - GetActorLocation();
	directionToPlayer.Normalize();

	FRotator newRotation = FMath::Lerp(stateRotation, directionToPlayer.Rotation(), attackTimer / attackSpeed);

	SetActorRotation(newRotation);

	if (attackTimer > attackSpeed) FireProjectile();
}

void ATurret::ScanBehavior()
{
	float yaw = FMath::Cos(GetGameTimeSinceCreation()) * FMath::DegreesToRadians(scanAngle);
	FRotator newRotation = FRotator(0, yaw, 0);

	SetActorRotation(GetActorRotation() + newRotation);

	if (FVector::Distance(GetActorLocation(), player->GetActorLocation()) < alertRadius && !isAlerted && GetAngleTowards(player->GetActorLocation()) < alertAngle)
	{
		stateRotation = GetActorRotation();
		isAlerted = true;
	}
}

void ATurret::ResetBehavior()
{
	if (isResetting == false)
	{
		stateRotation = GetActorRotation();
		isResetting = true;
	}

	float yaw = FMath::Cos(GetGameTimeSinceCreation()) * scanSpeed / scanAngle;
	FRotator adjustedRotation = startRotation + FRotator(0, yaw, 0);
	FRotator newRotation = FMath::Lerp(stateRotation, adjustedRotation, resetTimer / resetSpeed);

	SetActorRotation(newRotation);

	if (resetTimer > resetSpeed)
	{
		resetTimer = 0;
		isAlerted = false;
	}
}

void ATurret::StunBehavior()
{
	if (stunTimer > stunDuration)
	{
		stunTimer = 0;
		isStunned = false;
	}
}

void ATurret::TakeDamage(float damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("IT HIT ME!!"));

	isStunned = true;
	attackTimer = 0;
	resetTimer = 0;
	stunTimer = 0;
}
