// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/PP_GameState.h"

#include "PP_PingPongTypes.h"

void APP_GameState::AddScore(ETeam TeamMissedGoal)
{
    if (TeamMissedGoal == ETeam::Blue)
    {
        ++RedScore;
    }
    else if (TeamMissedGoal == ETeam::Red)
    {
        ++BlueScore;
    }
}