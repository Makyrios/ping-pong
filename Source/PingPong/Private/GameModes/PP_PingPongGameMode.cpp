// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PP_PingPongGameMode.h"

#include "PP_PingPongTypes.h"
#include "Actors/PP_Ball.h"
#include "Player/PlayerController/PP_PlatformPlayerController.h"
#include "Player/PlayerState/PP_PlayerState.h"
#include "GameStates/PP_GameState.h"
#include "Components/SlateWrapperTypes.h"

APawn* APP_PingPongGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    return nullptr;
}

void APP_PingPongGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    HandlePlayerLoad(NewPlayer);
}

void APP_PingPongGameMode::HandlePlayerLoad(APlayerController* NewPlayer)
{
    HandleLoginBeforeGameStart(NewPlayer);

    LoadedPlayers += 1;
    if (LoadedPlayers == 2)
    {
        OnAllPlayersLoaded();
    }
}

void APP_PingPongGameMode::HandleLoginBeforeGameStart(APlayerController* NewPlayer)
{
    APP_PlatformPlayerController* PongPlayerController = Cast<APP_PlatformPlayerController>(NewPlayer);
    APP_PlayerState* PongPlayerState = NewPlayer->GetPlayerState<APP_PlayerState>();

    if (GetNumPlayers() == 1 && PongPlayerState && PongPlayerController)
    {
        PongPlayerState->SetTeam(ETeam::Blue);
        PongPlayerController->SetWaitingTextVisibility(ESlateVisibility::Visible);
    }
    else if (GetNumPlayers() == 2 && PongPlayerState && PongPlayerController)
    {
        PongPlayerState->SetTeam(ETeam::Red);
    }

    SpawnPlayerByTeam(PongPlayerController, PongPlayerState->GetTeamAsString());
}

void APP_PingPongGameMode::SpawnPlayerByTeam(APlayerController* NewPlayer, const FString& Team)
{
    if (!NewPlayer) return;

    SpawnNewPawn(NewPlayer);
    MovePawnToPlayerStart(NewPlayer, Team);
}

void APP_PingPongGameMode::SpawnNewPawn(APlayerController* NewPlayer)
{
    if (!NewPlayer) return;
    // Spawn at empty location
    FVector SpawnLocation = FVector(0, 0, 1000);
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnLocation, FRotator::ZeroRotator);
    NewPlayer->Possess(NewPawn);
}

void APP_PingPongGameMode::MovePawnToPlayerStart(APlayerController* NewPlayer, const FString& Team)
{
    APP_PlatformPlayerController* PongPlayerController = Cast<APP_PlatformPlayerController>(NewPlayer);
    if (!PongPlayerController) return;

    AActor* PlayerStart = FindPlayerStart(PongPlayerController, Team);
    if (PlayerStart)
    {
        PongPlayerController->UpdatePawnTransform(PlayerStart->GetActorTransform());
    }
}

void APP_PingPongGameMode::OnAllPlayersLoaded()
{
    HideWaitingText();
    ShowScoreWidget();
    StartGame();
}

void APP_PingPongGameMode::HideWaitingText()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (APP_PlatformPlayerController* PongPlayerController = Cast<APP_PlatformPlayerController>(It->Get()))
        {
            PongPlayerController->SetWaitingTextVisibility(ESlateVisibility::Collapsed);
        }
    }
}

void APP_PingPongGameMode::ShowScoreWidget()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APP_PlatformPlayerController* PongPlayerController = Cast<APP_PlatformPlayerController>(It->Get());
        if (PongPlayerController)
        {
            PongPlayerController->SetScoreWidgetVisibility(ESlateVisibility::Visible);
        }
    }
}

void APP_PingPongGameMode::StartGame()
{
    Ball = GetWorld()->SpawnActor<APP_Ball>(BallClass, BallSpawnLocation, FRotator::ZeroRotator);
    ResetBall(GetRandomBallSpawnRotation());
}

FRotator APP_PingPongGameMode::GetRandomBallSpawnRotation(ETeam Team) const
{
    if (Team == ETeam::None)
    {
        bool bBlueTeam = FMath::RandBool();
        if (bBlueTeam)
        {
            Team = ETeam::Blue;
        }
        else
        {
            Team = ETeam::Red;
        }
    }

    if (Team == ETeam::Blue)
    {
        return BlueBallSpawnRotations[FMath::RandRange(0, BlueBallSpawnRotations.Num() - 1)];
    }
    else if (Team == ETeam::Red)
    {
        return RedBallSpawnRotations[FMath::RandRange(0, RedBallSpawnRotations.Num() - 1)];
    }

    return FRotator::ZeroRotator;
}

void APP_PingPongGameMode::ResetBall(const FRotator& SpawnRotation)
{
    ToggleInput(false);
    Ball->ResetMovement();
    Ball->SetActorLocation(BallSpawnLocation);
    FTimerHandle BallMoveTimer;
    GetWorld()->GetTimerManager().SetTimer(BallMoveTimer, FTimerDelegate::CreateWeakLambda(this, [&, SpawnRotation]()
    {
        Ball->StartMovement(SpawnRotation);
        ToggleInput(true);
    }), BallMoveDelay, false);
}

void APP_PingPongGameMode::ToggleInput(bool bEnableInput)
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (!It->Get()) return;

        APP_PlatformPlayerController* PongPlayerController = Cast<APP_PlatformPlayerController>(It->Get());
        if (PongPlayerController)
        {
            PongPlayerController->ToggleInput(bEnableInput);
        }
    }
}

void APP_PingPongGameMode::GoalMissed(ETeam TeamMissedGoal)
{
    PP_GameState = PP_GameState ? PP_GameState.Get() : GetWorld()->GetGameState<APP_GameState>();
    if (!PP_GameState) return;

    PP_GameState->AddScore(TeamMissedGoal);

    OnGoalScored.Broadcast(PP_GameState->GetBlueScore(), PP_GameState->GetRedScore());

    ResetBall(GetRandomBallSpawnRotation(TeamMissedGoal));
    ResetPlayers();
}

void APP_PingPongGameMode::ResetPlayers()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (!It->Get()) continue;
        if (APP_PlayerState* PP_PlayerState = It->Get()->GetPlayerState<APP_PlayerState>())
        {
            MovePawnToPlayerStart(It->Get(), PP_PlayerState->GetTeamAsString());
        }
    }
}