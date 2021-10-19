// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Pawns/Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float Deltatime) 
{

	Super::Tick(Deltatime);

	if (InFireRange())
	{
		RotateTurrent(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	//Since it is a single player game
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//Initialize the timer here

	//Timer manager is like the manager of the different timer handlers
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (InFireRange()) 
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}