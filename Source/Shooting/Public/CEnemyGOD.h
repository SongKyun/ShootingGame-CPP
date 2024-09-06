// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyGOD.generated.h"

UCLASS()
class SHOOTING_API ACEnemyGOD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyGOD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateEnemy();

	UPROPERTY(EditAnywhere)
	float delayTime = 2.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemyActor> enemyfactory;

	// 적이 스폰될 위치 기억 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> spawnPoints;
	//TArray<FVector> spawnPoints;

	UFUNCTION(BlueprintImplementableEvent)
	void FindSpawnPoints();

private:
	float currentTime = 0;
};