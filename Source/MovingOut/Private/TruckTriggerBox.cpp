// Fill out your copyright notice in the Description page of Project Settings.


#include "TruckTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Product.h"
#include "Engine/Engine.h"
#include "MovingOutCharacter.h"
#include "Net/UnrealNetwork.h"
#include "MoivingOutGameInstance.h"

// Sets default values
ATruckTriggerBox::ATruckTriggerBox()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;


   boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
   RootComponent = boxComp;
   boxComp->SetBoxExtent(FVector(100));

   //BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
   //BodyMesh->SetupAttachment(RootComponent);
   bReplicates = true;
}

// Called when the game starts or when spawned
void ATruckTriggerBox::BeginPlay()
{
   Super::BeginPlay();

   boxComp->OnComponentBeginOverlap.AddDynamic(this, &ATruckTriggerBox::OnComponentBeginOverlap);
   boxComp->OnComponentEndOverlap.AddDynamic(this, &ATruckTriggerBox::OnComponentEndOverlap);

   if (HasAuthority())
   {
      auto owner = GetWorld()->GetFirstPlayerController();
      SetOwner(owner);
   }
}

// Called every frame
void ATruckTriggerBox::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   //브랜치 추가

   if (count == 13)
   {   
      //엔딩위젯 걸린 맵으로 이동
      //GetWorld()->ServerTravel("/Game/Map/MovingTest?Listen", true);
      GetWorld()->ServerTravel("/Game/Map/EndingMap?Listen", true);
   }
}


void ATruckTriggerBox::ServerOnRep_CountUpdated()
{
   //prop이 가지고있는 bValidProp 이 true이면
   if (count < 15) {
   //   //유효횟수 추가
      UMoivingOutGameInstance* gi = GetWorld()->GetGameInstance<UMoivingOutGameInstance>();
      count++;
      gi->finalcount = count;
   }
   //GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("It's Prop")));
   //MultiOnRep_CountUpdated();
}

void ATruckTriggerBox::ServerOnRep_CountMinus()
{
   if (count > 0)
   {
      UMoivingOutGameInstance* gi = GetWorld()->GetGameInstance<UMoivingOutGameInstance>();
      count--;
      gi->finalcount = count;
   }
}

void ATruckTriggerBox::MultiOnRep_CountUpdated_Implementation()
{
}



void ATruckTriggerBox::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   //trucktiggerbox에 prop이 들어왔는지 확인
   AProduct* prop = Cast<AProduct>(OtherActor);
   //GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("OnComponentBeginOverlap")));
   // prop이라면
   if (prop && prop->bValidProp == false)
   //if (prop && prop->bValidProp && bCountCheck == true)
   {
      //GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("bValidProp")));
      prop->BodyMesh->SetMaterial(0, prop->overlapMat);
      prop->bValidProp = true;
      bCountCheck = false;
      ServerOnRep_CountUpdated();
   }

}

void ATruckTriggerBox::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   AProduct* prop = Cast<AProduct>(OtherActor);
   if (prop)
   {
      prop->BodyMesh->SetMaterial(0, prop->endoverlapMat);
      prop->bValidProp = false;
      bCountCheck = true;
      //GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, FString::Printf(TEXT("Velo %f"), v.Size()));
      ServerOnRep_CountMinus();
   }
}

void ATruckTriggerBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
   Super::GetLifetimeReplicatedProps(OutLifetimeProps);
   DOREPLIFETIME(ATruckTriggerBox, count);
}
