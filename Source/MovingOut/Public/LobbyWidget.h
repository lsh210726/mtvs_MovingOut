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

	//추가
public:
	// 위젯에 tick 이벤트 함수 추가
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UButton* btn_NextMap;

	//로비에 모두 모이면 원래 게임맵으로 이동시키게 하기
	UFUNCTION()
	void OnClickInGame();

	class AMovingOutCharacter* player;
};
