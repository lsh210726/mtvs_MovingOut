// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "Player_Move.generated.h"

//MappingContext,UInputAction ����ϱ� ����
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
	
//FInputActionValue �Ű������� �޾Ƶ鿩 ��������
//�¿��̵�
void Move(const FInputActionValue& value);

//UFUNCTION(Server, Unreliable)
//void ServerMove(const FInputActionValue& value);
////
//UFUNCTION(NetMulticast, Unreliable)
//void MultiCastMove(const FInputActionValue& value);

//Jump �����Լ� ����
UFUNCTION()
void Jump() /*override*/;

private:
UPROPERTY(EditAnywhere)
class UPlayerBaseComponent* playerComp;
UPROPERTY(EditAnywhere)
	class UPlayer_Move* playerMove;

public:
//Input �� �ҷ��´�
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

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SettingCamera")
float directionX = 600;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SettingCamera")
float directionY = 1300;



};
