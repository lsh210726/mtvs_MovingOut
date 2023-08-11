// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Move.h"
#include <Components/InputComponent.h>
#include "MovingOutCharacter.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include "OnePersonCamera.h"



void UPlayer_Move::BeginPlay()
{
	Super::BeginPlay();

	
	cameraActor = Cast<AOnePersonCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), AOnePersonCamera::StaticClass()));
	player = Cast<AMovingOutCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingOutCharacter::StaticClass()));
	//UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	
}

void UPlayer_Move::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*playerComp = CreateDefaultSubobject<UPlayerBaseComponent>(TEXT("Base Component"));*/
}

void UPlayer_Move::SetupInputBinding(class UInputComponent* PlayerInputComponent)
{
	auto pInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//바인드
	//playerComp->SetupInputBinding(PlayerInputComponent);
	//PlayerInputComponent를 UEnhancedInputComponent 타입으로 형변환
	if (pInput)
	{		
		pInput->BindAction(MovementAction, ETriggerEvent::Triggered, this, &UPlayer_Move::Move);
		pInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &UPlayer_Move::Jump);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Not Binding!!!"));
	}
}


void UPlayer_Move::Move(const FInputActionValue& value)
{

	//UE_LOG(LogTemp,Warning,TEXT("Moving"));
	//Move함수(움직임) 구현
	//GetCharacterMovement()->SetMaxSpeed
	//GetCharacterMovement()->MaxWalkSpeed = speed;
	//
	const FVector2D MovementVector = value.Get<FVector2D>();
	const FRotator Rotation = me->Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); //좌우
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); //앞방향
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); //오른쪽방향
	me->AddMovementInput(ForwardDirection, MovementVector.Y); //전후방 움직임
	me->AddMovementInput(RightDirection, MovementVector.X); //좌우 움직임

	FVector dir = player->GetActorLocation();
	cameraActor->SetActorLocation(FVector(dir.X-1300, dir.Y+900,  670));
}


void UPlayer_Move::Jump()
{
me->Jump();
}
