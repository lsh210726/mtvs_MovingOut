// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovingOutGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MovingOutCharacter.h"
#include "MovingOutPlayerController.h"


AMovingOutGameModeBase::AMovingOutGameModeBase()
{
	// 블루프린트 클래스를 받아온다
	static ConstructorHelpers::FClassFinder<UBoxCountWidget> MainHUDWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Hong/UI/BP_BoxCountWidget.BP_BoxCountWidget'"));

	// TSubclassOf 템플릿 클래스 객체에 블루프린트 클래스를 넣어준다
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
			// 위젯을 뷰포트에 띄우는 함수
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

