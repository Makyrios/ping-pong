// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Pawn/PP_PlayerPlatform.h"

#include "GameFramework/FloatingPawnMovement.h"

APP_PlayerPlatform::APP_PlayerPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
    
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("Platform Mesh");
    RootComponent = PlatformMesh;
    
    bReplicates = true;
    NetUpdateFrequency = 200.f;

    PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Pawn Movement Component");
    PawnMovementComponent->SetIsReplicated(true);
}

void APP_PlayerPlatform::BeginPlay()
{
	Super::BeginPlay();

}

void APP_PlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (IsLocallyControlled())
    {
        Server_UpdateTransform(GetActorTransform());
    }
}

void APP_PlayerPlatform::Server_UpdateTransform_Implementation(const FTransform& Transform)
{
    SetActorTransform(Transform);
}

