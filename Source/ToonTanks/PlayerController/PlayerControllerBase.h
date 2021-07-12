// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public: 
	void SetPlayerEnableState(bool SetPlayerEnable);
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
private:
	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.0f;

	FTimerHandle RestartTimer;
};
