// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/PawnBase.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public APawnBase
{
	GENERATED_BODY()

public: 

	virtual void Tick(float Deltatime) override;

	FTimerHandle FireRateTimerHandle;

	float FireRate = 2.0f;

	void CheckFireCondition();

	void HandleDestruction();

protected:

	virtual void BeginPlay() override;

private:

	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRange = 1000.f;

	bool InFireRange();

};
