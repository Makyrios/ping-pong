// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PP_HUD.generated.h"

class UPP_ScoreWidget;
class UPP_PlayersWaitingWidget;

UCLASS()
class PINGPONG_API APP_HUD : public AHUD
{
	GENERATED_BODY()

public:
    void SetTeamScoreWidgetVisibility(ESlateVisibility Visibility) const;
    
    void SetTeamScore(int BlueScore, int RedScore) const;

    void SetWaitingTextVisibility(ESlateVisibility Visibility) const;
    
protected:
    virtual void PostInitializeComponents() override;
    
protected:
    UPROPERTY()
    TObjectPtr<UPP_ScoreWidget> ScoreWidget;
    UPROPERTY(EditDefaultsOnly, Category = "PP|Widgets")
    TSubclassOf<UUserWidget> ScoreWidgetClass;

    UPROPERTY()
    TObjectPtr<UPP_PlayersWaitingWidget> PlayersWaitingWidget;
    UPROPERTY(EditDefaultsOnly, Category = "PP|Widgets")
    TSubclassOf<UUserWidget> PlayersWaitingWidgetWidgetClass;
};
