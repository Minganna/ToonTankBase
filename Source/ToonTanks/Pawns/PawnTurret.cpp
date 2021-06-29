// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		FireRateTimerHandle,
		this, 
		&APawnTurret::CheckFireCondition,
		FireRate,
		true);

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	//Call base pawn class HandleDestruction to play effects
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerTank || ReturnDistanceToPlayer()>Firerange || !PlayerTank->GetIsPlayerAlive())
	{
		return;
	}
	RotateTurret(PlayerTank->GetActorLocation());

}

void APawnTurret::CheckFireCondition()
{
	//if Player ==null or is dead the bail
	if (!PlayerTank || !PlayerTank->GetIsPlayerAlive())
	{
		return;
	}
	// if Player is in range then fire
	if (ReturnDistanceToPlayer() <= Firerange)
	{
		//Fire
		Fire();
	}
	
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerTank)
	{
		return 0.0f;
	}

	float Distance = FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
	return Distance;
}
