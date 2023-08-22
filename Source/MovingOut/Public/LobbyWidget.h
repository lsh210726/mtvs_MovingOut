// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	virtual void NativeOnInitialized();

	//�߰�
public:
	// ������ tick �̺�Ʈ �Լ� �߰�
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_NextMap;

	//�κ� ��� ���̸� ���� ���Ӹ����� �̵���Ű�� �ϱ�
	UFUNCTION()
	void OnClickInGame();

	class AMovingOutCharacter* player;
};
