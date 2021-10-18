// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "../Projectile.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);

}


void APawnBase::RotateTurrent(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurrentMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurrentMesh->SetWorldRotation(LookAtRotation);
}


void APawnBase::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPoint->GetComponentRotation());

}



