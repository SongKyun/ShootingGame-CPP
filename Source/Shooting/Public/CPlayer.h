// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "CPlayer.generated.h"

UCLASS()
class SHOOTING_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// box collision comp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;

	// 이동속도 속성
	UPROPERTY(EditAnywhere, Category = "Settings") // 에디터에 노출하기 위해 수정이 가능하게
		float speed = 500;

	float h;
	float v;
	void Horizontal(float Value);
	void Vertical(float Value);

	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ACBullet> bulletFactory;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireSound();

	void PauseInput();
};