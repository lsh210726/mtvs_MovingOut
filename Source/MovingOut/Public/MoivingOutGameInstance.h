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

	//gameInstance의 beginplay 개념
	virtual void Init() override;

	UPROPERTY()
	FString mySessionName;

	//세션 온라인을 위한 인터페이스 생성
	IOnlineSessionPtr sessionInterface;

	TSharedPtr<FOnlineSessionSearch> sessionSearch;

public:
	
	//세션 만들기(방만들기)
	void CreateSession();

	//세션 만들기 성공했으면 처리할 함수
	void OnCreateMySession(FName sessionName, bool bWasSuccessful);

	//세션 조인 함수
	void JoinMySession();

	//조인이 성공적으로 되었다면 처리할 함수
	void OnJoinMySession(FName sessionName, EOnJoinSessionCompleteResult::Type result);

	bool isEnterMainMap=false;

	  //게임종료를 하기위한 변수
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Final")
   int32 finalcount = 0;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Final")
   float finalTime = 0;
	
};
