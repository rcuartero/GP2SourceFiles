#include "Player/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Created FPS Camera"));
	check(CameraComponent != nullptr);

	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;

	if (!physicsHandleLeft) physicsHandleLeft = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle Left"));
	if (!physicsHandleRight) physicsHandleRight = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle Right"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	health = maxHealth;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ManageTelekinesis();

	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// Set up look around
	PlayerInputComponent->BindAxis("Yaw", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Pitch", this, &APlayerCharacter::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	// Activate Telekinesis
	PlayerInputComponent->BindAction("LeftHand", IE_Pressed, this, &APlayerCharacter::LeftHandActivate);
	PlayerInputComponent->BindAction("RightHand", IE_Pressed, this, &APlayerCharacter::RightHandActivate);

	// Deactivate Telekineses
	PlayerInputComponent->BindAction("LeftHand", IE_Released, this, &APlayerCharacter::LeftHandDeactivate);
	PlayerInputComponent->BindAction("RightHand", IE_Released, this, &APlayerCharacter::RightHandDeactivate);

	// Interact
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

	// Hold range change
	PlayerInputComponent->BindAction("IncreaseHoldRange", IE_Pressed, this, &APlayerCharacter::IncreaseHoldRange);
	PlayerInputComponent->BindAction("DecreaseHoldRange", IE_Pressed, this, &APlayerCharacter::DecreaseHoldRange);

	PlayerInputComponent->BindAction("IncreaseHoldRange", IE_Released, this, &APlayerCharacter::StopHoldRangeChange);
	PlayerInputComponent->BindAction("DecreaseHoldRange", IE_Released, this, &APlayerCharacter::StopHoldRangeChange);
}

void APlayerCharacter::MoveForward(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, value);
}

void APlayerCharacter::MoveRight(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, value);
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::LeftHandActivate()
{
	HandActivate(true);
}

void APlayerCharacter::RightHandActivate()
{
	HandActivate(false);
}

void APlayerCharacter::HandActivate(bool isLeftHand)
{
	AActor* hand = isLeftHand ? leftCaughtItem : rightCaughtItem;

	if (hand != nullptr) return;

	// Create array to ignore owner
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());

	// Output  hit array
	TArray<FHitResult> hitArray;
	FHitResult hitRay;


	// Use Line trace for precision telekinetic activation
	const bool HitLine = UKismetSystemLibrary::LineTraceSingle(GetWorld(), CameraComponent->GetComponentLocation(), CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * telekinesisRange), UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hitRay, true, FLinearColor::Red, FLinearColor::Blue, 1.0f);

	if (HitLine)
	{
		if (ITelekinetic* telekineticRay = Cast<ITelekinetic>(hitRay.GetActor()))
		{
			if (telekineticRay->isCaught == false)
			{
				telekineticRay->Caught();
				hand = hitRay.GetActor();
			}
		}
	}
	
	// Use sphere trace in case player misses line trace
	if (hand == nullptr)
	{
		const bool HitSphere = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetRootComponent()->GetComponentLocation(), GetRootComponent()->GetComponentLocation() + GetActorForwardVector().Normalize(), telekinesisRange, UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hitArray, true, FLinearColor::Red, FLinearColor::Blue, 1.0f);

		if (HitSphere)
		{
			for (FHitResult hit : hitArray)
			{
				if (ITelekinetic* telekinetic = Cast<ITelekinetic>(hit.GetActor()))
				{
					if (telekinetic->isCaught == false && GetAngleTowards(hit.GetActor()->GetActorLocation()) < telekinesisAngle)
					{
						telekinetic->Caught();
						hand = hit.GetActor();
						break;
					}
				}
			}
		}
	}

	if (isLeftHand && hand!= nullptr)
	{
		UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(hand->GetComponentByClass(UPrimitiveComponent::StaticClass()));
		physicsHandleLeft->GrabComponentAtLocationWithRotation(primitive, FName(*hand->GetName()), hand->GetActorLocation(), hand->GetActorRotation());
		leftCaughtItem = hand;
	}

	else if (hand != nullptr)
	{
		UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(hand->GetComponentByClass(UPrimitiveComponent::StaticClass()));
		physicsHandleRight->GrabComponentAtLocationWithRotation(primitive, FName(*hand->GetName()), hand->GetActorLocation(), hand->GetActorRotation());
		rightCaughtItem = hand;
	}
}

void APlayerCharacter::LeftHandDeactivate()
{
	if (ITelekinetic* item = Cast<ITelekinetic>(leftCaughtItem)) item->Released();
	leftCaughtItem = nullptr;
	//isLeashedLeft = false;
	physicsHandleLeft->ReleaseComponent();
}

void APlayerCharacter::RightHandDeactivate()
{
	if (ITelekinetic* item = Cast<ITelekinetic>(rightCaughtItem)) item->Released();
	rightCaughtItem = nullptr;
	physicsHandleRight->ReleaseComponent();
}

void APlayerCharacter::Interact()
{
	TArray<FHitResult> hitArray;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());

	const bool HitSphere = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetRootComponent()->GetComponentLocation(), GetRootComponent()->GetComponentLocation() + GetActorForwardVector().Normalize(), interactRange, UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hitArray, true, FLinearColor::Green, FLinearColor::Gray, 1.0f);

	if (HitSphere)
	{
		for (FHitResult hit : hitArray)
		{
			if (IInteractable* interactable = Cast<IInteractable>(hit.GetActor()))
			{
				interactable->OnInteract();
			}
		}
	}
}

void APlayerCharacter::ManageTelekinesis()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	if (isChangingRange)
	{
		holdRange += holdRangeChangeRate;
		holdRange = FMath::Clamp(holdRange, 0.0f, maxHoldRange);
	}

	if (leftCaughtItem != nullptr || rightCaughtItem != nullptr)
	{
		if (leftCaughtItem != nullptr)
		{
			FVector leftHandLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(handOffset.X + holdRange, -handOffset.Y, handOffset.Z));
			FRotator leftHandRotation = CameraRotation;

			physicsHandleLeft->SetTargetLocationAndRotation(leftHandLocation, leftHandRotation);
		}

		if (rightCaughtItem != nullptr)
		{
			FVector rightHandLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(handOffset.X + holdRange, handOffset.Y, handOffset.Z));
			FRotator rightHandRotation = CameraRotation;

			physicsHandleRight->SetTargetLocationAndRotation(rightHandLocation, rightHandRotation);
		}
	}
}

void APlayerCharacter::TakeDamage(float damage)
{
	health -= damage;

	ACatchThisGameModeBase* gameMode = Cast<ACatchThisGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	float healthPercentage = health / maxHealth;

	gameMode->currentWidget->SetHealthBar(healthPercentage);

	LeftHandDeactivate();
	RightHandDeactivate();

	if (health <= 0) UGameplayStatics::OpenLevel(GetWorld(), "LossMenu");
}

float APlayerCharacter::GetAngleTowards(FVector objectLocation)
{
	FVector vectorToObject = objectLocation - CameraComponent->GetComponentLocation();
	vectorToObject.Normalize();

	FVector vectorForward = CameraComponent->GetForwardVector();
	vectorForward.Normalize();

	float dotProduct = FVector::DotProduct(vectorToObject, vectorForward);
	float radians = FMath::Acos(dotProduct);
	float degrees = FMath::RadiansToDegrees(radians);

	return degrees;
}

void APlayerCharacter::IncreaseHoldRange()
{
	isChangingRange = true;
	holdRangeChangeRate = abs(holdRangeChangeRate);
}

void APlayerCharacter::DecreaseHoldRange()
{
	isChangingRange = true;
	holdRangeChangeRate = - abs(holdRangeChangeRate);
}

void APlayerCharacter::StopHoldRangeChange()
{
	isChangingRange = false;
}