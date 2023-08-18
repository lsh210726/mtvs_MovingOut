// Fill out your copyright notice in the Description page of Project Settings.


#include "Product.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values
AProduct::AProduct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->SetBoxExtent(FVector(10));*/

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	//BodyMesh->SetupAttachment(RootComponent);
	RootComponent=BodyMesh;

	//위젯컴포넌트 만들어주기
	WidGetComp= CreateDefaultSubobject<UWidgetComponent>(TEXT("WidGetComp"));
	//루트로 위젯컴프 
	WidGetComp->SetupAttachment(RootComponent);
	WidGetComp->SetRelativeLocation(FVector(1,1,1));
	WidGetComp->SetRelativeScale3D(FVector(1,1,1));

}

// Called when the game starts or when spawned
void AProduct::BeginPlay()
{
	Super::BeginPlay();
	WidGetComp->SetVisibility(false);
	
	
}

// Called every frame
void AProduct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

