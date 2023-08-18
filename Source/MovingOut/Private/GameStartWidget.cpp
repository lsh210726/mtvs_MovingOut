// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "Components/Button.h"
#include "MoivingOutGameInstance.h"

void UGameStartWidget::NativeConstruct()
{
	gi = GetGameInstance<UMoivingOutGameInstance>();
	if (gi)
	{
		// 뉴게임스타트 버튼 클릭 바인딩
		btn_NewGameStart->OnClicked.AddDynamic(this, &UGameStartWidget::OnClickNewGameStart);
		//게임 스타트 버튼 클릭 바인딩
		btn_GameStart->OnClicked.AddDynamic(this, &UGameStartWidget::OnClickGameStart);
	}
}

void UGameStartWidget::OnClickNewGameStart()
{
	if (gi)
	{
		gi->CreateSession();
	}
}

void UGameStartWidget::OnClickGameStart()
{
	if (gi)
	{
		gi->OnJoinMySession(FName("MovingOutTest Room"), EOnJoinSessionCompleteResult::Success);
	}
}
