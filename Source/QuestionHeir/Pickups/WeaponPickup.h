// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "QuestionHeir/WeaponComponent.h"
#include "WeaponPickup.generated.h"

UENUM(BlueprintType)
enum class EWeaponRarity:uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

/**
 * 
 */
UCLASS()
class QUESTIONHEIR_API AWeaponPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWeaponPickupMaterial();
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(BlueprintReadOnly)
	EWeaponRarity WeaponRarity = EWeaponRarity::Common;
	FWeaponStats WeaponStats;

private:
	void GenerateWeaponPickup();
	
	void AssignLegendaryStats();
	void AssignMasterStats();
	void AssignRareStats();
	void AssignCommonStats();
	
};
