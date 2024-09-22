// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PP_Gate.h"

#include "Actors/PP_Ball.h"
#include "Components/BoxComponent.h"
#include "GameModes/PP_PingPongGameMode.h"

APP_Gate::APP_Gate()
{
	PrimaryActorTick.bCanEverTick = false;

    GoalVolume = CreateDefaultSubobject<UBoxComponent>("Goal Volume");
    RootComponent = GoalVolume;
}

void APP_Gate::BeginPlay()
{
	Super::BeginPlay();

    GoalVolume->OnComponentBeginOverlap.AddDynamic(this, &APP_Gate::OnGateOverlap);
}

void APP_Gate::OnGateOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& Hit)
{
    if (OtherActor->IsA(APP_Ball::StaticClass()))
    {
        GameMode = GameMode ? GameMode.Get() : GetWorld()->GetAuthGameMode<APP_PingPongGameMode>();
        if (GameMode)
        {
            GameMode->GoalMissed(Team);
        }
    }
}
