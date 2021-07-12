// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "TimerManager.h"



void APlayerControllerBase::SetPlayerEnableState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}

void APlayerControllerBase::GameHasEnded(AActor * EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
