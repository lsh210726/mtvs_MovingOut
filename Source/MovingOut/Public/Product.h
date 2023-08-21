// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Product.generated.h"

UCLASS()
class MOVINGOUT_API AProduct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProduct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Prop")
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Prop")
	class UStaticMeshComponent* BodyMesh;

	//위젯컴포턴트 선언
	UPROPERTY(VisibleAnywhere,Category="prop")
	class UWidgetComponent* WidGetComp;

	//트럭에 넣는 유효한 박스인지 확인하기
	UPROPERTY(EditAnywhere, Category="Prop")
	bool bValidProp = false;

	//true1 false2 로 진행
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Prop")
	bool PropUI_1 = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
   FVector prevVelocity;

   UPROPERTY(EditAnywhere, Category=prop)
   class USoundBase* productSound;

   	bool bDoOnce=true; //두온스
	//타이머
	FTimerHandle GravityTimerHandle;
	float GravityTime=0.5f;

	//소리감쇠
	UPROPERTY(EditAnywhere, Category = prop)
	class USoundAttenuation* AttenuationSettings;

	//히트이벤트
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
