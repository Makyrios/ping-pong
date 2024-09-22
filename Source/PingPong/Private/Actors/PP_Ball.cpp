// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PP_Ball.h"

#include "GameFramework/ProjectileMovementComponent.h"

APP_Ball::APP_Ball()
{
	PrimaryActorTick.bCanEverTick = true;

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");
    RootComponent = BallMesh;

    BallMesh->SetCollisionObjectType(ECC_PhysicsBody);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
    MovementComponent->ProjectileGravityScale = 0.f;
    MovementComponent->InitialSpeed = 600.f;
    MovementComponent->MaxSpeed = 1400.f;
    MovementComponent->bShouldBounce = true;
    MovementComponent->Bounciness = 1.2f;
    MovementComponent->Friction = 0.f;
    
    MovementComponent->SetIsReplicated(true);
    
    bReplicates = true;
    NetUpdateFrequency = 200.f;
}

void APP_Ball::StartMovement(const FRotator& Direction)
{
    if (!MovementComponent) return;

    MovementComponent->Velocity = Direction.Vector() * MovementComponent->InitialSpeed;
}

void APP_Ball::ResetMovement()
{
    if (!MovementComponent) return;

    MovementComponent->StopMovementImmediately();
}

void APP_Ball::BeginPlay()
{
	Super::BeginPlay();
}

void APP_Ball::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Multicast_SetTransform(GetActorTransform());
}


void APP_Ball::Multicast_SetTransform_Implementation(const FTransform& NewTransform)
{
    SetActorTransform(NewTransform);
}