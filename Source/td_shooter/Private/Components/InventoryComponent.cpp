// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxWeaponsCount = 6;
	// ...
}

void UInventoryComponent::AddWeapon(AWeapon* Weapon)
{
	if (Inventory.Num() < MaxWeaponsCount)
	{
		Inventory.Add(Weapon);
	}
}

void UInventoryComponent::RemoveWeapon(AWeapon* Weapon)
{
	if (IsWeaponInInventory(Weapon))
	{
		Inventory.Remove(Weapon);
	}
}

void UInventoryComponent::UseWeaponAtSlot(int32 slot)
{
	AWeapon* Weapon = Inventory[slot];

	if (Weapon)
	{

		if (GetEquippedWeapons().Num() > 0) // Check if is there any equipped weapons
		{
			for (auto& EquippedWeapons : GetEquippedWeapons())
			{
				EquippedWeapons->OnInventoryUse(); // Hides all equipped weapons in case if EquippedWeapons > 1
			}
		}

		Weapon->OnInventoryUse(); // Take new Weapon
	}
}

const bool UInventoryComponent::IsWeaponInInventory(AWeapon* Weapon) const
{
	auto Index = Inventory.Find(Weapon);

	if (Index != INDEX_NONE)
	{
		return true;
	}

	return false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

TArray<AWeapon*> UInventoryComponent::GetEquippedWeapons() const
{
	TArray<AWeapon*> EquippedWeapons;

	for (auto Weapon : Inventory)
	{
		if (Weapon->bIsWeaponEquipped())
		{
			EquippedWeapons.Add(Weapon);
		}
	}

	return EquippedWeapons;
}

bool UInventoryComponent::IsAnyWeaponEquipped()
{
	for (auto Weapon : Inventory)
	{
		if (Weapon->bIsWeaponEquipped())
		{
			return true;
		}
	}

	return false;
}


