// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:
	//���� ��ŸƮ ��ư(������ ��ư-> ���������)
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MovingOut)
	class UButton* btn_NewGameStart;

	//���� ��ŸƮ ��ư(��� ��ư-> Ŭ���̾�Ʈ)
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MovingOut)
	class UButton* btn_GameStart;

	//�����ν��Ͻ� ���� ��������
	class UMoivingOutGameInstance* gi;

	//������ ��ŸƮ ��ư �Լ� (���� �����)
	UFUNCTION()
	void OnClickNewGameStart();
	
	//���� ��ŸƮ ��ư �Լ�(Ŭ���̾�Ʈ ���� �����ϱ�)
	UFUNCTION()
	void OnClickGameStart();
};
