// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "InventoryComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TD_SHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddWeapon(AWeapon* Weapon);

	void RemoveWeapon(AWeapon* Weapon);

	void UseWeaponAtSlot(int32 slot); //slot represents array index
	
	const bool IsWeaponInInventory(AWeapon* Weapon) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	TArray<AWeapon*> Inventory;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	int32 MaxWeaponsCount;

	TArray<AWeapon*> GetEquippedWeapons() const;

	bool IsAnyWeaponEquipped();
		
};
