// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"
#include "MovingOutCharacter.h"

// Sets default values for this component's properties
UPlayerBaseComponent::UPlayerBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


void UPlayerBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<AMovingOutCharacter>(GetOwner());
	moveComp = me->GetCharacterMovement();

	//ourChar->GetCharacterMovement()->MaxWalkSpeed = speed;

	// ���ε�
	/*me->onInputBindingDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);*/

}

// Called when the game starts
void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UPlayerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UPlayerBaseComponent::SetupInputBinding(class UInputComponent* PlayerInputComponent)
//{
//	
//}

