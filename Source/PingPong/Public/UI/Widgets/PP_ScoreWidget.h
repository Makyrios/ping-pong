// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PP_ScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class PINGPONG_API UPP_ScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> BlueScoreText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<UTextBlock> RedScoreText;

public:
    void SetTeamScore(int BlueScore, int RedScore) const;
};
