// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/InteractComponent.h"
#include "ShooterCharacter.h"
#include "Components/InventoryComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));

	RootComponent = InteractBox;

	WeaponMesh->SetupAttachment(RootComponent);

	bEquipped = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Shoot()
{
	if (!bEquipped)
	{
		return;
	}

	if (CurrentAmmo > 0)
	{
		CurrentAmmo--;

		//trace line or something
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bEquipped)
	{
		AddActorWorldRotation(FRotator(0.0f, 1.0f, 0.0f));
	}
}

void AWeapon::OnInventoryUse()
{
	if (bEquipped)
	{
		bEquipped = false;
		//Hide
	}
	else
	{
		bEquipped = true;
		//Attach To Player
	}
}

const bool AWeapon::bIsWeaponEquipped() const
{
	return bEquipped;
}

void AWeapon::OnInteract(UInteractComponent* InteractedWith)
{
	AShooterCharacter* Character = Cast<AShooterCharacter>(InteractedWith->GetOwner());

	Character->GetInventoryComponent()->AddWeapon(this);

	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
}

