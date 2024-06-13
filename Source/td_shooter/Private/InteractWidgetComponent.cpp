// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidgetComponent.h"

#include "Styling/SlateBrush.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Math/Color.h"

void UInteractWidgetComponent::SetItemImage(UTexture2D* Text)
{
	if (ItemImage)
	{
		ItemImage->SetOpacity(1.0f);
		ItemImage->SetBrushFromTexture(Text);
	}
}

void UInteractWidgetComponent::SetItemName(FText Name)
{
	ItemName->SetText(Name);
}

void UInteractWidgetComponent::ShowInteractWidget()
{
	//this->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UInteractWidgetComponent::HideInteractWidget()
{
	//this->SetBackgroundColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
}
