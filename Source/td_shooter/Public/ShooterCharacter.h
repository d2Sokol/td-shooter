// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "ShooterCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInteractComponent;
class UBoxComponent;
class UInventoryComponent;
class UInventoryWidget;
class AWeapon;

UCLASS()
class TD_SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBoxComponent* GetInteractBox();

	UInventoryComponent* GetInventoryComponent();

	UInventoryWidget* GetInventoryWidget();

	void SetCurrentWeapon(AWeapon* Weapon);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InputMove(const FInputActionValue& Value);

	void InputInventory(const FInputActionValue& Value);

	void HandleCharacterRotation();

	void StartShootingWeapon();

	void StopShootingWeapon();

private:


	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UInteractComponent* InteractComponent;

	UPROPERTY(EditAnywhere)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractBox;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* inputMappingContext;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* inputMove;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* inputInventory;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* inputShoot;

	AWeapon* CurrentWeapon;


	//HUD

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere)
	class UInventoryWidget* InventoryWidget;

};
