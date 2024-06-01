// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Weapon.h"
#include "Styling/SlateBrush.h"

#include "Components/Image.h"



void UInventoryWidget::AddWeaponToSlot(int32 SlotToChange, AWeapon* Weapon)
{
	UImage* ImageToEdit = nullptr;

	switch (SlotToChange)
	{
	case 1:
		ImageToEdit = SLOT_1_IMAGE;
		break;
	case 2:
		ImageToEdit = SLOT_2_IMAGE;
		break;
	case 3:
		ImageToEdit = SLOT_3_IMAGE;
		break;
	case 4:
		ImageToEdit = SLOT_4_IMAGE;
		break;
	case 5:
		ImageToEdit = SLOT_5_IMAGE;
		break;
	case 6:
		ImageToEdit = SLOT_6_IMAGE;
		break;
	default:
		break;
	}

	if (ImageToEdit)
	{
		ImageToEdit->SetOpacity(1.0f);
		ImageToEdit->SetBrushFromTexture(Weapon->GetInventoryIcon());
		/*FSlateBrush imageBrush{};
		imageBrush.ImageSize = FVector2D{1.0f, 1.0f};
		imageBrush.SetResourceObject(Weapon->GetInventoryIcon().LoadSynchronous());*/
	}
}

void UInventoryWidget::RemoveWeaponFromSlot(int32 SlotToChange)
{
	UImage* ImageToEdit = nullptr;

	switch (SlotToChange)
	{
	case 1:
		ImageToEdit = SLOT_1_IMAGE;
		break;
	case 2:
		ImageToEdit = SLOT_2_IMAGE;
		break;
	case 3:
		ImageToEdit = SLOT_3_IMAGE;
		break;
	case 4:
		ImageToEdit = SLOT_4_IMAGE;
		break;
	case 5:
		ImageToEdit = SLOT_5_IMAGE;
		break;
	case 6:
		ImageToEdit = SLOT_6_IMAGE;
		break;
	default:
		break;
	}

	if (ImageToEdit)
	{
		ImageToEdit->SetOpacity(0.0f);
	}
}
