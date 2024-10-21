// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

#include "../Characters/PlayerCharacter.h"

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateWeaponPickup();
	UpdateWeaponPickupMaterial();
}

void AWeaponPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		if (!Player->HasWeapon())
		{
			Player->EquipWeapon(true, WeaponStats);
			Destroy();
		}
	}
}

void AWeaponPickup::GenerateWeaponPickup()
{
	int Rarity = FMath::RandRange(1,100);
	
	if(1 <= Rarity && Rarity <= 50)
	{
		WeaponRarity = EWeaponRarity::Common;
		AssignCommonStats();
	}else if(51 <= Rarity && Rarity <= 80)
	{
		WeaponRarity = EWeaponRarity::Rare;
		AssignRareStats();
	}else if(81 <= Rarity && Rarity <= 95)
	{
		WeaponRarity = EWeaponRarity::Master;
		AssignMasterStats();
		
	}else if(96 <= Rarity && Rarity <= 100)
	{
		WeaponRarity = EWeaponRarity::Legendary;
		AssignLegendaryStats();
	}
}

void AWeaponPickup::AssignLegendaryStats()
{
	WeaponStats.Accuracy = FMath::RandRange(0.98f,1.0f);
	WeaponStats.FireRate = FMath::RandRange(0.05f,0.2f);
	WeaponStats.BaseDamage = FMath::RandRange(15.0f,30.0f);
	WeaponStats.MagazineSize = FMath::RandRange(20,100);
	WeaponStats.ReloadTime = FMath::RandRange(0.1f, 1.0f);

	int RandBad = FMath::Rand() & 5;

	switch(RandBad)
	{
	case 0:
		WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
		break;
	case 1:
		WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
		break;
	case 2:
		WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
		break;
	case 3:
		WeaponStats.MagazineSize = FMath::RandRange(1,19);
		break;
	case 4:
		WeaponStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
		break;
	}
}

void AWeaponPickup::AssignMasterStats()
{
	WeaponStats.Accuracy = FMath::RandRange(0.98f,1.0f);
	WeaponStats.FireRate = FMath::RandRange(0.05f,0.2f);
	WeaponStats.BaseDamage = FMath::RandRange(15.0f,30.0f);
	WeaponStats.MagazineSize = FMath::RandRange(20,100);
	WeaponStats.ReloadTime = FMath::RandRange(0.1f, 1.0f);

	TArray<int> RandArray = {0, 1, 2, 3, 4};
	int RandBad1 = RandArray[FMath::Rand() % 5];
	RandArray.Remove(RandBad1); //Ensure the same stat isn't selected twice
	int RandBad2 = RandArray[FMath::Rand() % 4];
	
	switch(RandBad1)
	{
	case 0:
		WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
		break;
	case 1:
		WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
		break;
	case 2:
		WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
		break;
	case 3:
		WeaponStats.MagazineSize = FMath::RandRange(1,19);
		break;
	case 4:
		WeaponStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
		break;
	}

	switch(RandBad2)
	{
	case 0:
		WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
		break;
	case 1:
		WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
		break;
	case 2:
		WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
		break;
	case 3:
		WeaponStats.MagazineSize = FMath::RandRange(1,19);
		break;
	case 4:
		WeaponStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
		break;
	}
}

void AWeaponPickup::AssignRareStats()
{
	WeaponStats.Accuracy = FMath::RandRange(0.98f,1.0f);
	WeaponStats.FireRate = FMath::RandRange(0.05f,0.2f);
	WeaponStats.BaseDamage = FMath::RandRange(15.0f,30.0f);
	WeaponStats.MagazineSize = FMath::RandRange(20,100);
	WeaponStats.ReloadTime = FMath::RandRange(0.1f, 1.0f);

	TArray<int> RandArray = {0, 1, 2, 3, 4};
	int RandBad1 = RandArray[FMath::Rand() % 5];
	RandArray.Remove(RandBad1); //Ensure the same stat isn't selected twice
	int RandBad2 = RandArray[FMath::Rand() % 4];
	RandArray.Remove(RandBad2); //Ensure the same stat isn't selected twice
	int RandBad3 = RandArray[FMath::Rand() % 3];
	
	switch(RandBad1)
	{
	case 0:
		WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
		break;
	case 1:
		WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
		break;
	case 2:
		WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
		break;
	case 3:
		WeaponStats.MagazineSize = FMath::RandRange(1,19);
		break;
	case 4:
		WeaponStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
		break;
	}

	switch(RandBad2)
	{
	case 0:
		WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
		break;
	case 1:
		WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
		break;
	case 2:
		WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
		break;
	case 3:
		WeaponStats.MagazineSize = FMath::RandRange(1,19);
		break;
	case 4:
		WeaponStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
		break;
	}

	switch(RandBad3)
	{
	case 0:
		WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
		break;
	case 1:
		WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
		break;
	case 2:
		WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
		break;
	case 3:
		WeaponStats.MagazineSize = FMath::RandRange(1,19);
		break;
	case 4:
		WeaponStats.ReloadTime = FMath::RandRange(1.0f, 4.0f);
		break;
	}
}

void AWeaponPickup::AssignCommonStats()
{
	WeaponStats.Accuracy = FMath::RandRange(0.9f,0.98f);
	WeaponStats.FireRate = FMath::RandRange(0.2f,1.0f);
	WeaponStats.BaseDamage = FMath::RandRange(5.0f,15.0f);
	WeaponStats.MagazineSize = FMath::RandRange(1,19);
}
