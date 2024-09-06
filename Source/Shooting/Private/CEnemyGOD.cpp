// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyGOD.h"
#include "CEnemyActor.h"
#include "Kismet/GameplayStatics.h"
#include "CShootGameMode.h"

// Sets default values
ACEnemyGOD::ACEnemyGOD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyGOD::BeginPlay()
{
	Super::BeginPlay();

    FindSpawnPoints();

    FTimerHandle TimerHandle;

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACEnemyGOD::CreateEnemy, delayTime, true);

    TArray<AActor*> allActors;
    // spawnPoint 들 찾아오기
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
    // 이들 중에서 spawnpoint만 찾아서 가져오자
    for (auto actor : allActors)
    {
        // 이름이 spawnpoint 를 포함하고 있으면
        if (actor->GetName().Contains("SpawnPoint"))
        {
            // 가져오기
            spawnPoints.Add(actor);
        }
    }
}

// Called every frame
void ACEnemyGOD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACEnemyGOD::CreateEnemy()
{
    // 게임의 상태가 Ready, Start, Playing 일때만 이동가능
    auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
    if (gm && gm->myState != EShootGameState::Playing)
    {
        return;
    }

    // spawnPoint가 없으면 처리하지 않도록
    if (spawnPoints.Num() < 1)
    {
        return;
    }

    // spawnpoints 중에 랜덤한 위치를 뽑아서 그 위치에 생성하도록 하자
    // 1. 랜덤한 스폰 인덱스 추출하기
    int spawnIndex = FMath::RandRange(0, spawnPoints.Num()-1); // Max 포함
    // 2. 스폰할 위치
    FVector loc = spawnPoints[spawnIndex]->GetActorLocation();
    // 3. 생성하자
    GetWorld()->SpawnActor<ACEnemyActor>(enemyfactory, loc, FRotator::ZeroRotator);

    //    // 경과시간이 생성 시간을 초과했다면?
    //if (currentTime > delayTime)
    //{
    //    currentTime = 0;

    //    ACEnemyActor* spawnActor = GetWorld()->SpawnActor<ACEnemyActor>(enemyfactory, GetActorLocation(), GetActorRotation());
    //}
    //else
    //{
    //    // currentTime = currentTime + DeltaTime;
    //    currentTime += DeltaTime;
    //}
}