// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingOutPlayerController.h"
#include "MovingOutGameModeBase.h"

AMovingOutPlayerController::AMovingOutPlayerController()
{
	bReplicates = true;
}

void AMovingOutPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMovingOutPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));

	
}

void AMovingOutPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	if (HasAuthority())
	{
		gm = GetWorld()->GetAuthGameMode<AMovingOutGameModeBase>();
	}
	auto gi = Cast<UMoivingOutGameInstance>(GetWorld()->GetGameInstance());
	if (IsLocalPlayerController() && gi && gi->isEnterMainMap)
	{
		InvokeEntering();
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

void AMovingOutPlayerController::InvokeEntering_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("InvokeEntering"));
	//auto gm = Cast<AMovingOutGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm)
	{
		gm->CountPlayer();
	}
}

void AMovingOutPlayerController::OnEnterLevel_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("OnEnterLevel_Implementation gm : %s"), gm==nullptr?TEXT("NULL"):TEXT("Valid"));

	auto gi = Cast<UMoivingOutGameInstance>(GetWorld()->GetGameInstance());

	gi->isEnterMainMap = true;
	if (gm)
	{
		gm->CountPlayer();
	}
}

void AMovingOutPlayerController::GoToEnd_Implementation()
{
	
	GetWorld()->ServerTravel("/Game/Map/EndingMap?Listen", true);

}
