// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PP_PingPongTypes.h"
#include "GameFramework/Actor.h"
#include "PP_Gate.generated.h"

class APP_PingPongGameMode;
class UBoxComponent;

UCLASS()
class PINGPONG_API APP_Gate : public AActor
{
    GENERATED_BODY()

public:
    APP_Gate();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnGateOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& Hit);

    
private:
    UPROPERTY(EditAnywhere, Category = "PP|Game")
    ETeam Team {ETeam::None};
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UBoxComponent> GoalVolume;
    
    UPROPERTY()
    TObjectPtr<APP_PingPongGameMode> GameMode;
};