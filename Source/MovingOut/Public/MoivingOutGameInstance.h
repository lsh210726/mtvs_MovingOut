// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MoivingOutGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MOVINGOUT_API UMoivingOutGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMoivingOutGameInstance();

	//gameInstance�� beginplay ����
	virtual void Init() override;

	UPROPERTY()
	FString mySessionName;

	//���� �¶����� ���� �������̽� ����
	IOnlineSessionPtr sessionInterface;

	TSharedPtr<FOnlineSessionSearch> sessionSearch;

public:
	
	//���� �����(�游���)
	void CreateSession();

	//���� ����� ���������� ó���� �Լ�
	void OnCreateMySession(FName sessionName, bool bWasSuccessful);

	//���� ���� �Լ�
	void JoinMySession();

	//������ ���������� �Ǿ��ٸ� ó���� �Լ�
	void OnJoinMySession(FName sessionName, EOnJoinSessionCompleteResult::Type result);
	
};
