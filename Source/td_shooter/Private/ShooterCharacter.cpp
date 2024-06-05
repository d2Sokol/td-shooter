// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon.h"

#include "Components/BoxComponent.h"
#include "Components/InteractComponent.h"
#include "Components/InventoryComponent.h"

#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	InteractBox->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	InventoryWidgetClass = nullptr;
	InventoryWidget = nullptr;
	CurrentWeapon = nullptr;


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && InventoryWidgetClass)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		check(PlayerController);
		InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryWidgetClass);
		check(InventoryWidget);
		InventoryWidget->AddToPlayerScreen();
	}

	
	APlayerController* PC = Cast<APlayerController>(Controller);

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void AShooterCharacter::InputMove(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();


	if (IsValid(Controller))
	{
		const FRotator Rotation = Camera->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, InputVector.Y / 2.0f);
		AddMovementInput(RightDirection, InputVector.X / 2.0f);
	}
}

void AShooterCharacter::InputInventory(const FInputActionValue& Value)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		int32 WEAPON_SLOT = 0;
		if (PlayerController->IsInputKeyDown(EKeys::One))
		{
			WEAPON_SLOT = 0;
		}
		else if (PlayerController->IsInputKeyDown(EKeys::Two))
		{
			WEAPON_SLOT = 1;
		}
		else if (PlayerController->IsInputKeyDown(EKeys::Three))
		{
			WEAPON_SLOT = 2;
		}
		else if (PlayerController->IsInputKeyDown(EKeys::Four))
		{
			WEAPON_SLOT = 3;
		}
		else if (PlayerController->IsInputKeyDown(EKeys::Five))
		{
			WEAPON_SLOT = 4;
		}
		else if (PlayerController->IsInputKeyDown(EKeys::Six))
		{
			WEAPON_SLOT = 5;
		}


		InventoryComponent->UseWeaponAtSlot(WEAPON_SLOT);
	}
}

void AShooterCharacter::HandleCharacterRotation()
{
	FVector MouseLocation, MouseDirection;

	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	float xMouse, yMouse;

	PController->GetMousePosition(xMouse, yMouse);

	FVector CharLoc = GetActorLocation();

	FVector2D CharInScreen;
	PController->ProjectWorldLocationToScreen(CharLoc, CharInScreen);

	FVector2D Result;
	Result.X = -(yMouse - CharInScreen.Y);
	Result.Y = xMouse - CharInScreen.X;


	// Get angle rotation and rotation Character
	float angle = FMath::RadiansToDegrees(FMath::Acos(Result.X / Result.Size()));

	if (Result.Y < 0)
		angle = 360 - angle;

	FRotator rot(0, angle+40.0f, 0);

	GetMesh()->SetWorldRotation(rot);
}

void AShooterCharacter::StartShootingWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartShooting();
	}
}

void AShooterCharacter::StopShootingWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopShooting();
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleCharacterRotation();
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(inputMappingContext, 0);
		}

		if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
			Input->BindAction(inputMove, ETriggerEvent::Triggered, this, &AShooterCharacter::InputMove);
			Input->BindAction(inputInventory, ETriggerEvent::Started, this, &AShooterCharacter::InputInventory);
			Input->BindAction(inputShoot, ETriggerEvent::Started, this, &AShooterCharacter::StartShootingWeapon);
			Input->BindAction(inputShoot, ETriggerEvent::Completed, this, &AShooterCharacter::StopShootingWeapon);
		}

		
		//PlayerEnhancedInputComponent->BindAction(inputMove, ETriggerEvent::Triggered, this, &APlayer0::InputMove);
	}
}

UBoxComponent* AShooterCharacter::GetInteractBox()
{
	return InteractBox;
}

UInventoryComponent* AShooterCharacter::GetInventoryComponent()
{
	return InventoryComponent;
}

UInventoryWidget* AShooterCharacter::GetInventoryWidget()
{
	return InventoryWidget;
}

void AShooterCharacter::SetCurrentWeapon(AWeapon* Weapon)
{
	CurrentWeapon = Weapon;
}

