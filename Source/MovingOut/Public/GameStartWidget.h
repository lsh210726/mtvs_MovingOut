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
	//게임 스타트 버튼(새게임 버튼-> 서버만들기)
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MovingOut)
	class UButton* btn_NewGameStart;

	//게임 스타트 버튼(계속 버튼-> 클라이언트)
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MovingOut)
	class UButton* btn_GameStart;

	//게임인스턴스 변수 가져오기
	class UMoivingOutGameInstance* gi;

	//뉴게임 스타트 버튼 함수 (세션 만들기)
	UFUNCTION()
	void OnClickNewGameStart();
	
	//게임 스타트 버튼 함수(클라이언트 세션 조인하기)
	UFUNCTION()
	void OnClickGameStart();
};
