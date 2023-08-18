// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingOutPlayerController.h"
#include "MovingOutGameModeBase.h"

void AMovingOutPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMovingOutPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AMovingOutPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		gm = GetWorld()->GetAuthGameMode<AMovingOutGameModeBase>();
	}

}

void AMovingOutPlayerController::ServerRespawnPlayer_Implementation()
{
	if (gm != nullptr)
	{
		APawn* playerPawn = GetPawn();
		UnPossess();

		playerPawn->Destroy();

		//처음 배정받은 playerStart 액터 위치에서 리스폰
		//gm->RestartPlayer(this);

		//지정된 transform에서  리스폰 위치 정해줄때
		FTransform  restartPoint;
		restartPoint.SetLocation(FVector(570,390,182));
		gm->RestartPlayerAtTransform(this, restartPoint);
	}
}
