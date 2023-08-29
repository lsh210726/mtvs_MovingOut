// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingOutCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "PlayerBaseComponent.h"
#include "Product.h"
#include "Player_Move.h"
#include <kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include "PropOne_UI.h"
#include "PropTwo_UI.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <EngineUtils.h>
#include "MovingOutGameModeBase.h"
#include <Components/BoxComponent.h>

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

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
    boxComp->SetupAttachment(RootComponent);
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
    boxComp->OnComponentBeginOverlap.AddDynamic(this, &AMovingOutCharacter::OnComponentBeginOverlap);
    boxComp->OnComponentEndOverlap.AddDynamic(this, &AMovingOutCharacter::OnComponentEndOverlap);


    //prop->SetVisibility(ESlateVisibility::Hidden);


    /*FTimerHandle changCamera;
    GetWorldTimerManager().SetTimer(changCamera, this, &AMovingOutCharacter::ChangeCamera, 1.0f, false);

    /*if (GetController() != nullptr && GetController()->IsLocalPlayerController()) {
       pc = Cast<AMovingOutPlayerController>(GetController());
       pc->Possess(this);
    }

    if (HasAuthority())
    {

    }*/
    
}

// Called every frame
void AMovingOutCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GrabObjectContinue();

   
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

     //1,2용인지 숫자 UI표시 인풋값
    auto pInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    //바인드
    //playerComp->SetupInputBinding(PlayerInputComponent);
    //PlayerInputComponent를 UEnhancedInputComponent 타입으로 형변환
    if (pInput)
    {
        pInput->BindAction(SwitchUIAction, ETriggerEvent::Started, this, &AMovingOutCharacter::OnToggleUI);
        pInput->BindAction(SwitchUIAction, ETriggerEvent::Completed, this, &AMovingOutCharacter::OffToggleUI);
    }

    //이승형 코드
    PlayerInputComponent->BindAction(TEXT("GrabObject"), IE_Pressed, this, &AMovingOutCharacter::GrabObjectStart);
    PlayerInputComponent->BindAction(TEXT("GrabObject"), IE_Released, this, &AMovingOutCharacter::GrabObjectEnd);
    PlayerInputComponent->BindAction(TEXT("ShootObject"), IE_Pressed, this, &AMovingOutCharacter::ShootObject);
    PlayerInputComponent->BindAction(TEXT("GoToEndingMap"),IE_Pressed , this, &AMovingOutCharacter::GotoEndingMap);
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
    //UE_LOG(LogTemp,Warning,TEXT("dddddddd"));

    //월드에 있는 Product 부모클래스를 가진 Actor들을 모두 찾는다
    //배열로 가져오기
    /**/TArray<AActor*> arrOutActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProduct::StaticClass(), arrOutActors);
    //배열에 담은 변수를 AProduct 캐스트
    for (AActor* actor : arrOutActors) //어레이에서 하나하나 불러서 뭔가 해주겠다
    {
        AProduct* prop = Cast<AProduct>(actor); //AProduct 캐스트

        if (prop != nullptr && prop->bValidProp == false)
        {//캐스트가 true면
            prop->WidGetComp->SetVisibility(true);
            prop->BodyMesh->SetRenderCustomDepth(true);
        }
    }
    /*for (TActorIterator<AProduct> It(GetWorld()); It; ++It)
    {
       AProduct* spawn = *It;
       spawn->WidGetComp->SetVisibility(true);
    }*/
}
void AMovingOutCharacter::OffToggleUI()
{
    //월드에 있는 Product 부모클래스를 가진 Actor들을 모두 찾는다
    //배열로 가져오기
    /**/TArray<AActor*> arrOutActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProduct::StaticClass(), arrOutActors);
    //배열에 담은 변수를 AProduct 캐스트
    for (AActor* actor : arrOutActors)
    {
        AProduct* prop = Cast<AProduct>(actor);
        if (prop != nullptr && prop->bValidProp == false)//만약 캐스트가 true면
        {
            prop->WidGetComp->SetVisibility(false);
            prop->BodyMesh->SetRenderCustomDepth(false);
        }
    }
    
    //    else
    //    {
    //        // UI 위젯을 뷰포트에서 제거합니다.
    //        livingSwitchUI_One->RemoveFromParent();
    //        livingSwitchUI_OneInstance = nullptr;
}

void AMovingOutCharacter::ServerCountPlayer_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("ServerCountPlayer"));
	gm = Cast<AMovingOutGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("gggg"));
		gm->CountPlayer();
	}
}

void AMovingOutCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AProduct* prop = Cast<AProduct>(OtherActor);
   // prop이라면
   
   if (prop && bGrab == false)
   //if (prop && prop->bValidProp && bCountCheck == true)
   {
      prop->BodyMesh->SetRenderCustomDepth(true);
   }
}

void AMovingOutCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   AProduct* prop = Cast<AProduct>(OtherActor);
   // prop이라면
   if (prop)
   //if (prop && prop->bValidProp && bCountCheck == true)
   {
       prop->BodyMesh->SetRenderCustomDepth(false);
   }
}

void AMovingOutCharacter::GotoEndingMap()
{   
    GetWorld()->ServerTravel("/Game/Map/EndingMap?Listen", true);
}

void AMovingOutCharacter::GrabObjectStart_Implementation()
 {

}

void AMovingOutCharacter::GrabObjectEnd_Implementation()
{

}

void AMovingOutCharacter::GrabObjectContinue_Implementation()
{

}

void AMovingOutCharacter::ShootObject_Implementation()
{

}

/*void AMovingOutCharacter::ChangeCamera()
{
   if (GetController() != nullptr && GetController()->IsLocalPlayerController()) {

      movingoutCamera = Cast<AOnePersonCamera>(UGameplayStatics::GetActorOfClass(this, AOnePersonCamera::StaticClass()));
      pc = Cast<AMovingOutPlayerController>(GetController());
      pc->SetViewTarget(movingoutCamera);
   }
}*/