// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurrentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables", meta = (AllowPrivateAccess = "true"))
		//int VisibleAnywhereint = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = "true"))
		//int EditAnywhereInt = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

protected: 
	
	void RotateTurrent(FVector LookAtTarget);

	void Fire();

public:
	// Sets default values for this pawn's properties
	APawnBase();

};
