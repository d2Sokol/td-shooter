// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TD_SHOOTER_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UImage* SLOT_1_IMAGE;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* SLOT_2_IMAGE;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* SLOT_3_IMAGE;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* SLOT_4_IMAGE;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* SLOT_5_IMAGE;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* SLOT_6_IMAGE;

	void AddWeaponToSlot(int32 Slot, class AWeapon* Weapon);

	void RemoveWeaponFromSlot(int32 Slot);
	
};
