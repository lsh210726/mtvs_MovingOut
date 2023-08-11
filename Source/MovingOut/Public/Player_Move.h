// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "Player_Move.generated.h"

//MappingContext,UInputAction 사용하기 위함
class UInputMappingContext;
class UInputAction;

UCLASS()
class MOVINGOUT_API UPlayer_Move : public UPlayerBaseComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;
	
//FInputActionValue 매개변수를 받아들여 참조전달
//좌우이동
void Move(const FInputActionValue& value);
//Jump 가상함수 선언
void Jump() /*override*/;

private:
UPROPERTY(EditAnywhere)
class UPlayerBaseComponent* playerComp;
UPROPERTY(EditAnywhere)
	class UPlayer_Move* playerMove;

public:
//Input 을 불러온다
/*Enhanced input*/ 
UPROPERTY(EditAnywhere, Category=Input)
UInputMappingContext* MovingOutContext;
UPROPERTY(EditAnywhere, Category = Input)
UInputAction* MovementAction;
UPROPERTY(EditAnywhere, Category = Input)
UInputAction* JumpAction;

UPROPERTY(EditAnywhere, Category="Camera")
class AOnePersonCamera* cameraActor;

UPROPERTY(EditAnywhere)
class AMovingOutCharacter* player;

};
