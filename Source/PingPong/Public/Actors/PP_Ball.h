// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PP_Ball.generated.h"

class UProjectileMovementComponent;
class APP_PingPongGameMode;

UCLASS()
class PINGPONG_API APP_Ball : public AActor
{
	GENERATED_BODY()
	
public:	
	APP_Ball();

    void StartMovement(const FRotator& Direction);
    void ResetMovement();

protected:
	virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override; 

private:
    UFUNCTION(NetMulticast, Unreliable)
    void Multicast_SetTransform(const FTransform& NewTransform);

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BallMesh;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UProjectileMovementComponent> MovementComponent;
    
};
