// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PP_ScoreWidget.h"

#include "Components/TextBlock.h"

void UPP_ScoreWidget::SetTeamScore(int BlueScore, int RedScore) const
{
    BlueScoreText->SetText(FText::AsNumber(BlueScore));
    RedScoreText->SetText(FText::AsNumber(RedScore));
}