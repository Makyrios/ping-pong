// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PP_PlayerPlatform.generated.h"


class UFloatingPawnMovement;

UCLASS()
class PINGPONG_API APP_PlayerPlatform : public APawn
{
	GENERATED_BODY()

public:
	APP_PlayerPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
    
    UFUNCTION(Server, Unreliable)
    void Server_UpdateTransform(const FTransform& Location);

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> PlatformMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TObjectPtr<UFloatingPawnMovement> PawnMovementComponent;
};
