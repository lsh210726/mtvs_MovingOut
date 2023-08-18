// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingOutCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "PlayerBaseComponent.h"
#include "Player_Move.h"
#include "PropOne_UI.h"
#include "PropTwo_UI.h"
#include "Kismet/GameplayStatics.h"
#include "MovingOutPlayerController.h"
#include "OnePersonCamera.h"

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
	//방어코드

	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(MovingOutContext, 0);
		}
	
	}


	FTimerHandle changCamera;
	GetWorldTimerManager().SetTimer(changCamera, this, &AMovingOutCharacter::ChangeCamera, 1.0f, false);

	/*if (GetController() != nullptr && GetController()->IsLocalPlayerController()) {
		pc = Cast<AMovingOutPlayerController>(GetController());
		pc->Possess(this);
	}*/

	if (HasAuthority())
	{
		
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

	//Move 이동

	/*UEnhancedInputComponent* inputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (inputComp != nullptr)
	{
		inputComp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Move);
	}*/

	//onInputBindingDelegate.Broadcast(PlayerInputComponent);
	playerMove->SetupInputBinding(PlayerInputComponent);

	////바인드
	//playerComp->SetupInputBinding(PlayerInputComponent);
	////PlayerInputComponent를 UEnhancedInputComponent 타입으로 형변환
	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	//{		
	//EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Move);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMovingOutCharacter::Jump);
}


void AMovingOutCharacter::Move(const FInputActionValue& value)
{
	//move함수(움직임) 구현
	//const FVector2D movementvector = value.Get<FVector2D>();
	////const frotator rotation = controller->getcontrolrotation();
	////const frotator yawrotation(0.f, rotation.yaw, 0.f); //좌우
	//const FVector forwarddirection = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::X); //앞방향
	//AddMovementInput(forwarddirection, movementvector.Y); //전후방 움직임
	//const FVector rightdirection = FRotationMatrix(GetController()->GetControlRotation()).GetUnitAxis(EAxis::Y); //오른쪽방향
	//AddMovementInput(rightdirection, movementvector.X); //좌우 움직임
}



//void AMovingOutCharacter::Jump()
//{
//Super::Jump();*/ //Character.h에 있는 Jump사용.
//}


void AMovingOutCharacter::OnToggleUI()
{
 //if (!IsValid(livingSwitchUI_OneInstance))
  //  {
  //      // UI 위젯을 생성하고 뷰포트에 추가합니다.
  //      livingSwitchUI_One = CreateWidget<livingSwitchUI_One>(this, livingSwitchUI_One::StaticClass());
  //      if (livingSwitchUI_One)
  //      {
  //          UIWidgetInstance->AddToViewport();
  //      }
  //  }
  //  else
  //  {
  //      // UI 위젯을 뷰포트에서 제거합니다.
  //      livingSwitchUI_One->RemoveFromParent();
  //      livingSwitchUI_OneInstance = nullptr;
}

void AMovingOutCharacter::ChangeCamera()
{
	if (GetController() != nullptr && GetController()->IsLocalPlayerController()) {

		movingoutCamera = Cast<AOnePersonCamera>(UGameplayStatics::GetActorOfClass(this, AOnePersonCamera::StaticClass()));
		pc = Cast<AMovingOutPlayerController>(GetController());
		pc->SetViewTarget(movingoutCamera);
	}
}

