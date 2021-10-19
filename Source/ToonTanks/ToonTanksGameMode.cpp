// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		HandleGameOver(false);
		if (ToonTanksPlayerController) 
		{
			//Disable input for the Tank 
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTurrents -= 1;
		if (TargetTurrents == 0)
		{
			HandleGameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TurrentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), TurrentActors);

	TargetTurrents = TurrentActors.Num();

	
	HandleGameStart();

}


void AToonTanksGameMode::HandleGameStart()
{
	//Setting the tank
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController) 
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
	}

}

void AToonTanksGameMode::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);

	//stop the timer for each of the turrents
	TArray<AActor*> TurrentActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), TurrentActors);
	
	for (int i = 0; i < TurrentActors.Num(); ++i) {
		TurrentActors[i]->GetWorldTimerManager().ClearTimer(Cast<ATower>((TurrentActors[i]))->FireRateTimerHandle);
	}
}