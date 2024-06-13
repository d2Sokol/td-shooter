// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/InteractComponent.h"
#include "ShooterCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "InteractWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	MuzzleEffectLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Effect Location"));
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));

	RootComponent = InteractBox;

	WeaponMesh->SetupAttachment(RootComponent);
	MuzzleEffectLocation->SetupAttachment(RootComponent);

	InventoryComponent = nullptr;

	bPickedUp = false;

	WeaponMetadata.bEquipped = false;

	WeaponMetadata.CurrentAmmo = 120;

	WeaponMetadata.bIsAmmoUnlimited = false;

	if (InteractWidget)
	{
		InteractWidget->SetupAttachment(RootComponent);
		InteractWidget->SetWidgetSpace(EWidgetSpace::World);

		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/BP_InteractWidget") };
		if (WidgetClass.Succeeded())
		{
			InteractWidget->SetWidgetClass(WidgetClass.Class);
		}
	}

	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (UInteractWidget* IntWidget = Cast<UInteractWidget>(InteractWidget->GetUserWidgetObject()))
	{


		IntWidget->SetItemImage(WeaponMetadata.InventoryIcon);
		IntWidget->SetItemName(FText::FromString(WeaponMetadata.ItemName));
		IntWidget->HideInteractWidget();
	}

	Character = Cast<AShooterCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (Character)
	{
		InventoryComponent = Character->GetInventoryComponent();
	}
	
	
}

void AWeapon::StartShooting()
{
	GetWorldTimerManager().SetTimer(ShootHandle, this, &AWeapon::Shoot, ShootDelay, true);
}

void AWeapon::StopShooting()
{
	GetWorldTimerManager().ClearTimer(ShootHandle);
}



void AWeapon::Shoot()
{
	if (!WeaponMetadata.bEquipped)
	{
		return;
	}

	

	if (WeaponMetadata.CurrentAmmo > 0)
	{
		if (!WeaponMetadata.bIsAmmoUnlimited)
			WeaponMetadata.CurrentAmmo--;

		FHitResult Hit;

		FVector TraceStart = GetActorLocation();
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 2000.0f;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
		UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

		if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
			if (HitEffect) {
				//UNiagaraFunctionLibrary::SpawnSystemAttached(FireEffectMuzzle, MuzzleEffectLocation, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint);
			}
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
		}

		if (FireEffectMuzzle) {
			UNiagaraFunctionLibrary::SpawnSystemAttached(FireEffectMuzzle, MuzzleEffectLocation, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
		}
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!bPickedUp)
	{
		AddActorWorldRotation(FRotator(0.0f, 1.0f, 0.0f));
	}
}

void AWeapon::OnInventoryUse()
{
	if (WeaponMetadata.bEquipped)
	{
		Character->SetCurrentWeapon(nullptr);
		WeaponMetadata.bEquipped = false;
		this->SetActorHiddenInGame(true);
	}
	else
	{
		Character->SetCurrentWeapon(this);
		WeaponMetadata.bEquipped = true;
		this->SetActorHiddenInGame(false);
	}
}

const bool AWeapon::bIsWeaponEquipped() const
{
	return WeaponMetadata.bEquipped;
}

void AWeapon::OnInteract(UInteractComponent* InteractedWith)
{
	if (InventoryComponent)
	{
		InventoryComponent->AddWeapon(this);
		bPickedUp = true;
		this->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
		this->SetActorRelativeLocation(FVector(0.0f, -30.0f, 15.0f));
		this->SetActorRelativeRotation(FRotator(0.0f, -180.0f, 0.0f));
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);

	}
}

void AWeapon::OnStartIntersecting()
{
	if (InteractWidget)
	{
		if (UInteractWidget* IntWidget = Cast<UInteractWidget>(InteractWidget->GetUserWidgetObject()))
		{
			IntWidget->ShowInteractWidget();
		}
		
	}
}

void AWeapon::OnStopIntersecting()
{
	if (InteractWidget)
	{
		if (UInteractWidget* IntWidget = Cast<UInteractWidget>(InteractWidget->GetUserWidgetObject()))
		{
			IntWidget->HideInteractWidget();
		}

	}
}

class UTexture2D* AWeapon::GetInventoryIcon()
{
	return WeaponMetadata.InventoryIcon;
}

