// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MovingOutCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, class UInputComponent*);

//MappingContext,UInputAction ����ϱ� ����
class UInputMappingContext;
class UInputAction;

//camera, spring arm ����ϱ� ����

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MOVINGOUT_API AMovingOutCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMovingOutCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



private:
	
	//Move�� �̵�

	/*camera,spring arm ����*/
	/*UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;*/
	/*UPROPERTY(EditAnywhere)
	class UPlayerBaseComponent* playerComp;*/

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
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

public:
	// delegate
	//FInputBindingDelegate onInputBindingDelegate;


	void Move(const FInputActionValue& value);

public:
	//widget �� �����Ͽ��� ����ϱ� ����
	UPROPERTY(VisibleAnywhere, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Countwidget; 

	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class UBoxCountWidget> battleWidget;

	

};
