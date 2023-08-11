// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingOutCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "PlayerBaseComponent.h"
#include "Player_Move.h"

// Sets default values
AMovingOutCharacter::AMovingOutCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*Camera*/
	//ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	//ViewCamera->SetupAttachment(CameraBoom);
	//playerComp = CreateDefaultSubobject<UPlayerBaseComponent>(TEXT("Base Component"));
	playerMove = CreateDefaultSubobject<UPlayer_Move>(TEXT("PlayerMove"));
}

// Called when the game starts or when spawned
void AMovingOutCharacter::BeginPlay()
{
	Super::BeginPlay();
	//����ڵ�
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(MovingOutContext, 0);
		}
	}
}

// Called every frame
void AMovingOutCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovingOutCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Move �̵�

	/*UEnhancedInputComponent* inputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (inputComp != nullptr)
	{
		inputComp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Move);
	}*/

	//onInputBindingDelegate.Broadcast(PlayerInputComponent);
	playerMove->SetupInputBinding(PlayerInputComponent);

	////���ε�
	//playerComp->SetupInputBinding(PlayerInputComponent);
	////PlayerInputComponent�� UEnhancedInputComponent Ÿ������ ����ȯ
	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	//{		
	//EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Move);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Jump);
}


void AMovingOutCharacter::Move(const FInputActionValue& value)
{
	//move�Լ�(������) ����
	//const FVector2D movementvector = value.Get<FVector2D>();
	////const frotator rotation = controller->getcontrolrotation();
	////const frotator yawrotation(0.f, rotation.yaw, 0.f); //�¿�
	//const FVector forwarddirection = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::X); //�չ���
	//AddMovementInput(forwarddirection, movementvector.Y); //���Ĺ� ������
	//const FVector rightdirection = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::Y); //�����ʹ���
	//AddMovementInput(rightdirection, movementvector.X); //�¿� ������
}

//void AMovingOutCharacter::Jump()
//{
//Super::Jump();*/ //Character.h�� �ִ� Jump���.
//}



