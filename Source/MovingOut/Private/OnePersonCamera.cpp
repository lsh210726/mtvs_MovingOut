// Fill out your copyright notice in the Description page of Project Settings.


#include "OnePersonCamera.h"
#include "MovingOutCharacter.h"
#include "Kismet/GameplayStatics.h"

AOnePersonCamera::AOnePersonCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	RegisterAllActorTickFunctions(true, false);
}

void AOnePersonCamera::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AMovingOutCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingOutCharacter::StaticClass()));

	//this->SetActorRelativeLocation(FVector(0,0,0));
	//this->SetActorRelativeRotation(FRotator(0,0,0));
}

void AOnePersonCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp,Warning,TEXT("in"));
	
	

}


