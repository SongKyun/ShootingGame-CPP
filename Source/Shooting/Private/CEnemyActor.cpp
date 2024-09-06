#include "CEnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACEnemyActor::ACEnemyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    // Default SubObject
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    RootComponent = BoxComp;

    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootComponent);

    // ���� ���
    ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

    if (TempMesh.Succeeded())
    {
        BodyMesh->SetStaticMesh(TempMesh.Object);
    }

    ConstructorHelpers::FObjectFinder<UMaterial>TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

    if (TempMat.Succeeded())
    {
        BodyMesh->SetMaterial(0, TempMat.Object);
    }

    BoxComp->SetBoxExtent(FVector(50.0f));
    BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));
    BodyMesh->SetCollisionProfileName(TEXT("NoCollision"));

    BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemyActor::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void ACEnemyActor::BeginPlay()
{
    Super::BeginPlay();
    
    Target = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
}

// Called every frame
void ACEnemyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsValid(Target))
    {
        Direction = Target->GetActorLocation() - GetActorLocation();
        Direction.Normalize();
    }
    FVector P0 = GetActorLocation();
    FVector vt = Direction * speed * DeltaTime;
    FVector P = P0 + vt;

    FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(P, P + Direction);
    FRotator rot = UKismetMathLibrary::MakeRotFromXZ(GetActorForwardVector(), Direction);

    SetActorLocation(P);
    SetActorRotation(rot);
}

void ACEnemyActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // �ε��� �༮�� ���̸�
    if (OtherActor->GetName().Contains("CEnemy"))
    {
        // -> ����(�ƹ� ó������ �ʴ´�)
        return;
    }

    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expFactory, GetActorLocation(), FRotator::ZeroRotator);

    // �ε��� �༮�� �÷��̾�� ���ӿ��� ó������
    auto player = Cast<ACPlayer>(OtherActor);
    if (player)
    {
        // ���� ���� ó��
    }


    OtherActor->Destroy();
    Destroy();
}
