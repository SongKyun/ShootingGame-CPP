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
    // spawnPoint �� ã�ƿ���
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
    // �̵� �߿��� spawnpoint�� ã�Ƽ� ��������
    for (auto actor : allActors)
    {
        // �̸��� spawnpoint �� �����ϰ� ������
        if (actor->GetName().Contains("SpawnPoint"))
        {
            // ��������
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
    // ������ ���°� Ready, Start, Playing �϶��� �̵�����
    auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
    if (gm && gm->myState != EShootGameState::Playing)
    {
        return;
    }

    // spawnPoint�� ������ ó������ �ʵ���
    if (spawnPoints.Num() < 1)
    {
        return;
    }

    // spawnpoints �߿� ������ ��ġ�� �̾Ƽ� �� ��ġ�� �����ϵ��� ����
    // 1. ������ ���� �ε��� �����ϱ�
    int spawnIndex = FMath::RandRange(0, spawnPoints.Num()-1); // Max ����
    // 2. ������ ��ġ
    FVector loc = spawnPoints[spawnIndex]->GetActorLocation();
    // 3. ��������
    GetWorld()->SpawnActor<ACEnemyActor>(enemyfactory, loc, FRotator::ZeroRotator);

    //    // ����ð��� ���� �ð��� �ʰ��ߴٸ�?
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