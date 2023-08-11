// Fill out your copyright notice in the Description page of Project Settings.


#include "TruckTriggerBox.h"
#include "Components/BoxComponent.h"

// Sets default values
ATruckTriggerBox::ATruckTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATruckTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = boxComp;
	boxComp->SetBoxExtent(FVector(10));
	
}

// Called every frame
void ATruckTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

