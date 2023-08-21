// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MovingOutPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API AMovingOutPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMovingOutPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	virtual void BeginPlay() override;

	UPROPERTY()
	class AMovingOutGameModeBase* gm;
	
	UFUNCTION(Server,Unreliable)
	void ServerRespawnPlayer();

	UFUNCTION(Server, Reliable)
	void InvokeEntering();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void OnEnterLevel();
};
