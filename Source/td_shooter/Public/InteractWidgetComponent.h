// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class TD_SHOOTER_API UInteractWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ItemName;

	void SetItemImage(UTexture2D* Image);

	void SetItemName(FText Name);

	void ShowInteractWidget();

	void HideInteractWidget();
};
