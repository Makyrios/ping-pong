// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PP_PingPongTypes.h"
#include "PP_PlayerState.generated.h"

UCLASS()
class PINGPONG_API APP_PlayerState : public APlayerState
{
    GENERATED_BODY()

    APP_PlayerState();

public:
    FORCEINLINE ETeam GetTeam() const { return Team; };

    FString GetTeamAsString() const;

    FORCEINLINE void SetTeam(ETeam NewTeam) { Team = NewTeam; };

protected:
    void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:
    UPROPERTY(VisibleAnywhere, Replicated)
    ETeam Team {ETeam::None};
};