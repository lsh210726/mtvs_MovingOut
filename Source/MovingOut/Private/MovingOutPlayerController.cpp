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

		//ó�� �������� playerStart ���� ��ġ���� ������
		//gm->RestartPlayer(this);

		//������ transform����  ������ ��ġ �����ٶ�
		FTransform  restartPoint;
		restartPoint.SetLocation(FVector(570,390,182));
		gm->RestartPlayerAtTransform(this, restartPoint);
	}
}
