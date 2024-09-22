// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PP_PingPongTypes.h"
#include "PP_GameState.generated.h"

UCLASS()
class PINGPONG_API APP_GameState : public AGameStateBase
{
	GENERATED_BODY()
    
public:
    // Add score to the team that scored the goal
    // TeamMissedGoal - the team that missed the goal
    void AddScore(ETeam TeamMissedGoal);

    FORCEINLINE int GetRedScore() const { return RedScore; }
    FORCEINLINE int GetBlueScore() const { return BlueScore; }

private:
    int RedScore {0};
    int BlueScore {0};
};
