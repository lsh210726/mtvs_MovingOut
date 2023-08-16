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

	//트럭에 넣는 유효한 박스인지 확인하기
	UPROPERTY(EditAnywhere, Category="Prop")
	bool bValidProp = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Prop")
	bool PropUI_1 = true; 
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Prop")
	bool PropUI_2 = true;

};
