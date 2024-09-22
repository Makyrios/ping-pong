// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/PP_HUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widgets/PP_PlayersWaitingWidget.h"
#include "UI/Widgets/PP_ScoreWidget.h"

void APP_HUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ScoreWidget = CreateWidget<UPP_ScoreWidget>(GetWorld(), ScoreWidgetClass);
    if (ScoreWidget)
    {
        ScoreWidget->AddToViewport();
        ScoreWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    PlayersWaitingWidget = CreateWidget<UPP_PlayersWaitingWidget>(GetWorld(), PlayersWaitingWidgetWidgetClass);
    if (PlayersWaitingWidget)
    {
        PlayersWaitingWidget->AddToViewport();
        PlayersWaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void APP_HUD::SetTeamScoreWidgetVisibility(ESlateVisibility Visibility) const
{
    if (!ScoreWidget) return;

    ScoreWidget->SetVisibility(Visibility);
}

void APP_HUD::SetTeamScore(int BlueScore, int RedScore) const
{
    if (!ScoreWidget) return;

    ScoreWidget->SetTeamScore(BlueScore, RedScore);
}

void APP_HUD::SetWaitingTextVisibility(ESlateVisibility Visibility) const
{
    if (!PlayersWaitingWidget) return;
    
    PlayersWaitingWidget->SetVisibility(Visibility);
}
