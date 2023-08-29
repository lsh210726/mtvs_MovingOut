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
	//1,2�ο� ����UI����ġ 
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SwitchUIAction;

	//���ǿ� ������ player�� üũ
	UPROPERTY(EditAnywhere, Category = Session)
	int32 playersNum;

public:
	// delegate
	//FInputBindingDelegate onInputBindingDelegate;


	void Move(const FInputActionValue& value);

	//1,2������ ���� UIǥ�� 
public:
	UFUNCTION()
	void OnToggleUI();
	UFUNCTION()
	void OffToggleUI();
public:
	//widget �� �����Ͽ��� ����ϱ� ����
	UPROPERTY(VisibleAnywhere, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Countwidget; 

	UPROPERTY()
	class UPropOne_UI* propSlot;

	UPROPERTY(EditAnywhere, Category = MySettings)
	TSubclassOf<class UBoxCountWidget> battleWidget;

	UFUNCTION(Server, Reliable)
	void ServerCountPlayer();

	class AMovingOutGameModeBase* gm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	int32 finalScore = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "MySettings")
	bool bFinalGame = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Truck")
    class UBoxComponent* boxComp;

   UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "MySettings")
   bool bGrab = false;

   UFUNCTION()
   void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

   UFUNCTION()
   void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

   UFUNCTION()
   void GotoEndingMap();

   //class AProduct* prop;



   //�̽��� �ڵ�
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
