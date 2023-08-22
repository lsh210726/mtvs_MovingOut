// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovingOutGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MovingOutCharacter.h"
#include "MovingOutPlayerController.h"


AMovingOutGameModeBase::AMovingOutGameModeBase()
{
	// �������Ʈ Ŭ������ �޾ƿ´�
	static ConstructorHelpers::FClassFinder<UBoxCountWidget> MainHUDWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Hong/UI/BP_BoxCountWidget.BP_BoxCountWidget'"));

	// TSubclassOf ���ø� Ŭ���� ��ü�� �������Ʈ Ŭ������ �־��ش�
	if (MainHUDWidgetAsset.Succeeded())
		MainHUDWidgetClass = MainHUDWidgetAsset.Class;


	DefaultPawnClass = AMovingOutCharacter::StaticClass();
	PlayerControllerClass = AMovingOutPlayerController::StaticClass();

}



void AMovingOutGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AMovingOutGameModeBase::CountPlayer()
{
	playerNum++;
	if (playerNum == 2)
	{
		bplayerMax = true;
	}
}

void AMovingOutGameModeBase::EnterMainMap()
{
	UE_LOG(LogTemp, Warning, TEXT("EnterMainMap"));

}

void AMovingOutGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainHUDWidgetClass))
	{
		MainHUDWidget = Cast<UBoxCountWidget>(CreateWidget(GetWorld(), MainHUDWidgetClass));

		if (IsValid(MainHUDWidget))
		{
			// ������ ����Ʈ�� ���� �Լ�
			MainHUDWidget->AddToViewport();
		}
	}
}


void AMovingOutGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("playerNum : %d"), playerNum);

	/*if ()
	{
	}*/
	
}

