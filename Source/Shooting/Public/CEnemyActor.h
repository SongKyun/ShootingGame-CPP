#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyActor.generated.h"

UCLASS()
class SHOOTING_API ACEnemyActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACEnemyActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // box collision comp
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* BoxComp;
    // static mesh comp
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* BodyMesh;
    //Mode Speed
    UPROPERTY(EditAnywhere, Category = "Settings")
    float speed = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Settings")
    class ACPlayer* Target;

    UFUNCTION()
    void OnComponentBeginOverlap
        (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
        bool bFromSweep, const FHitResult& SweepResult);

public:
    UPROPERTY(EditAnywhere)
    class UParticleSystem* expFactory;

private:
    FVector Direction;
};