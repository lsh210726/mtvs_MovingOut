// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartWidget.h"
#include "Components/Button.h"
#include "MoivingOutGameInstance.h"

void UGameStartWidget::NativeConstruct()
{
	gi = GetGameInstance<UMoivingOutGameInstance>();
	if (gi)
	{
		// �����ӽ�ŸƮ ��ư Ŭ�� ���ε�
		btn_NewGameStart->OnClicked.AddDynamic(this, &UGameStartWidget::OnClickNewGameStart);
		//���� ��ŸƮ ��ư Ŭ�� ���ε�
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
