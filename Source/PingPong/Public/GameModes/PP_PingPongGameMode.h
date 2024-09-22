// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PP_PingPongTypes.h"
#include "PP_PingPongGameMode.generated.h"

class APP_Ball;
class APP_GameState;
class APP_PlatformPlayerController;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGoalScored, int, int);

UCLASS()
class PINGPONG_API APP_PingPongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    FOnGoalScored OnGoalScored;

public:
    void GoalMissed(ETeam TeamMissedGoal);
    
protected:
    // Prevent default pawn spawn
    virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
    
    virtual void PostLogin(APlayerController* NewPlayer) override;

    void HandlePlayerLoad(APlayerController* NewPlayer);

    void HandleLoginBeforeGameStart(APlayerController* NewPlayer);
    
    void OnAllPlayersLoaded();

    void StartGame();

    void ResetBall(const FRotator& SpawnRotation);
    void ResetPlayers();

private:
    void ToggleInput(bool bEnableInput);
    
    void SpawnPlayerByTeam(APlayerController* NewPlayer, const FString& Team);

    void MovePawnToPlayerStart(APlayerController* NewPlayer, const FString& Team);
    void SpawnNewPawn(APlayerController* NewPlayer);

    void ShowScoreWidget();
    void HideWaitingText();

    FRotator GetRandomBallSpawnRotation(ETeam Team = ETeam::None) const;


private:
    UPROPERTY(EditAnywhere, Category = "PP|Game")
    float BallMoveDelay {2.f};
    
    UPROPERTY(EditAnywhere, Category = "PP|Game")
    TSubclassOf<APP_Ball> BallClass;
    
    UPROPERTY()
    TObjectPtr<APP_Ball> Ball;

    UPROPERTY()
    TObjectPtr<APP_GameState> PP_GameState;

    UPROPERTY(EditAnywhere, Category = "PP|Game")
    FVector BallSpawnLocation{0, 0, 30.f};
    UPROPERTY(EditAnywhere, Category = "PP|Game")
    TArray<FRotator> BlueBallSpawnRotations{
                                            {0, 0, 0},
                                            {0, 30.f, 0},
                                            {0, 60.f, 0},
                                            {0, -30.f, 0},
                                            {0, -60.f, 0}
                                                            };
    UPROPERTY(EditAnywhere, Category = "PP|Game")
    TArray<FRotator> RedBallSpawnRotations{
                                                {0, 180.f, 0},
                                                {0, 210.f, 0},
                                                {0, 240.f, 0},
                                                {0, 150.f, 0},
                                                {0, 120.f, 0}
    };
    
    
    int LoadedPlayers {0};

};
