// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerState/PP_PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Player/Pawn/PP_PlayerPlatform.h"


APP_PlayerState::APP_PlayerState()
{
    bReplicates = true;
}

FString APP_PlayerState::GetTeamAsString() const
{
    if (Team == ETeam::Blue)
    {
        return FString("Blue");
    }
    else if (Team == ETeam::Red)
    {
        return FString("Red");
    }
    
    return "None";
}

void APP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APP_PlayerState, Team);
}
