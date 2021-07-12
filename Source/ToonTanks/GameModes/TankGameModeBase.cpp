// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include"ToonTanks//Pawns/PawnTank.h"
#include"ToonTanks/Pawns/PawnTurret.h"
#include"Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerController/PlayerControllerBase.h"
#include "Engine/World.h"
#include "TimerManager.h"


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

int32 ATankGameModeBase::GetTurretsCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}


void ATankGameModeBase::ActorDied(AActor * DeadActor)
{
	if (DeadActor==PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnableState(false);
		}
	}
	else if(APawnTurret* DestroyedTurret=Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets -= 1;
		if (TargetTurrets<=0)
		{
			HandleGameOver(true);
		}
	}
}



void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTurretsCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnableState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
	GameStart();
}
void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
	if (PlayerControllerRef)
	{
		PlayerControllerRef->GameHasEnded(PlayerTank, PlayerWon);
	}
}



