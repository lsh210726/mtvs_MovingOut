// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MovingOutCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, class UInputComponent*);

//MappingContext,UInputAction 사용하기 위함
class UInputMappingContext;
class UInputAction;

//camera, spring arm 사용하기 위함

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
	
	//Move로 이동

	/*camera,spring arm 선언*/
	/*UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;*/
	/*UPROPERTY(EditAnywhere)
	class UPlayerBaseComponent* playerComp;*/

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
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

public:
	// delegate
	//FInputBindingDelegate onInputBindingDelegate;


	void Move(const FInputActionValue& value);

	

};
