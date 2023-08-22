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
	//1,2인용 리빙UI스위치 
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SwitchUIAction;

	//세션에 조인한 player수 체크
	UPROPERTY(EditAnywhere, Category = Session)
	int32 playersNum;

public:
	// delegate
	//FInputBindingDelegate onInputBindingDelegate;


	void Move(const FInputActionValue& value);

	//1,2용인지 숫자 UI표시 
public:
	UFUNCTION()
	void OnToggleUI();
	UFUNCTION()
	void OffToggleUI();
public:
	//widget 을 디테일에서 사용하기 위함
	UPROPERTY(VisibleAnywhere, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Countwidget; 

	UPROPERTY()
	class UPropOne_UI* propSlot;

	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class UBoxCountWidget> battleWidget;

	UFUNCTION(Server, Reliable)
	void ServerCountPlayer();

	class AMovingOutGameModeBase* gm;


   //이승형 코드
public:
   UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
      void GrabObjectStart();
   UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
      void GrabObjectEnd();
   UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
      void GrabObjectContinue();
   UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
      void ShootObject();
	
   /*class AMovingOutPlayerController* pc;


   class AOnePersonCamera* movingoutCamera;

   void ChangeCamera();*/
};
