#include "InteractWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInteractWidget::SetItemImage(UTexture2D* Texture)
{
	if (Texture)
	{
		Image->SetBrushFromTexture(Texture);
	}
}

void UInteractWidget::SetItemName(FText Text)
{
	Name->SetText(Text);
}

void UInteractWidget::ShowInteractWidget()
{
	if(!bIsOnScreen)
	{
		bIsOnScreen = true;
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInteractWidget::HideInteractWidget()
{
	bIsOnScreen = false;
	UE_LOG(LogTemp, Warning, TEXT("hidding"));
	this->SetVisibility(ESlateVisibility::Hidden);
}

bool UInteractWidget::IsWidgetOnScreen() const
{
	return bIsOnScreen;
}
