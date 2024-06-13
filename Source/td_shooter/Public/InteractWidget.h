// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class TD_SHOOTER_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetItemImage(UTexture2D* Texture);

	void SetItemName(FText Text);

	void ShowInteractWidget();

	void HideInteractWidget();

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* Image;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Name;

	bool IsWidgetOnScreen() const;

private:

	bool bIsOnScreen = false;
};
