// Copyright Epic Games, Inc. All Rights Reserved.


#include "MovingOutGameModeBase.h"
#include "Blueprint/UserWidget.h"


AMovingOutGameModeBase::AMovingOutGameModeBase()
{
	// �������Ʈ Ŭ������ �޾ƿ´�
	static ConstructorHelpers::FClassFinder<UBoxCountWidget> MainHUDWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Hong/UI/BP_BoxCountWidget.BP_BoxCountWidget'"));

	// TSubclassOf ���ø� Ŭ���� ��ü�� �������Ʈ Ŭ������ �־��ش�
	if (MainHUDWidgetAsset.Succeeded())
		MainHUDWidgetClass = MainHUDWidgetAsset.Class;
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


