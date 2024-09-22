// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerController/PP_PlatformPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameModes/PP_PingPongGameMode.h"
#include "UI/HUD/PP_HUD.h"


void APP_PlatformPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    if (APP_PingPongGameMode* GameMode = GetWorld()->GetAuthGameMode<APP_PingPongGameMode>())
    {
        GameMode->OnGoalScored.AddUObject(this, &ThisClass::UpdateScore);
    }
}

void APP_PlatformPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APP_PlatformPlayerController, PlayerPawn);
}

void APP_PlatformPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EIComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ThisClass::MoveForward);
        EIComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ThisClass::MoveRight);
    }
}

void APP_PlatformPlayerController::MoveForward(const FInputActionValue& Value)
{
    if (Value.GetMagnitude() == 0.0f) return;

    if (PlayerPawn)
    {
        PlayerPawn->AddMovementInput(PlayerPawn->GetActorForwardVector(), Value.GetMagnitude());
    }
}

void APP_PlatformPlayerController::MoveRight(const FInputActionValue& Value)
{
    if (PlayerPawn)
    {
        PlayerPawn->AddMovementInput(PlayerPawn->GetActorRightVector(), Value.GetMagnitude());
    }
}

void APP_PlatformPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    PlayerPawn = InPawn;
}

void APP_PlatformPlayerController::BlendCameraView(AActor* CameraActorToBlend)
{
    Client_BlendCameraView(CameraActorToBlend);
}

void APP_PlatformPlayerController::Client_BlendCameraView_Implementation(AActor* CameraActorToBlend)
{
    SetViewTarget(CameraActorToBlend, FViewTargetTransitionParams());
}

void APP_PlatformPlayerController::UpdatePawnTransform(const FTransform& NewPawnTransform)
{
    if (PlayerPawn)
    {
        PlayerPawn->SetActorLocationAndRotation(NewPawnTransform.GetLocation(), NewPawnTransform.GetRotation());
    }
}

void APP_PlatformPlayerController::UpdateScore(int BlueScore, int RedScore)
{
    Client_UpdateScore(BlueScore, RedScore);
}

void APP_PlatformPlayerController::Client_UpdateScore_Implementation(int BlueScore, int RedScore)
{
    HUD = HUD ? HUD.Get() : Cast<APP_HUD>(GetHUD());
    if (!HUD) return;

    HUD->SetTeamScore(BlueScore, RedScore);
}

void APP_PlatformPlayerController::SetScoreWidgetVisibility(ESlateVisibility Visibility)
{
    Client_SetScoreWidgetVisibility(Visibility);
}

void APP_PlatformPlayerController::Client_SetScoreWidgetVisibility_Implementation(ESlateVisibility Visibility)
{
    HUD = HUD ? HUD.Get() : Cast<APP_HUD>(GetHUD());
    if (!HUD) return;

    HUD->SetTeamScoreWidgetVisibility(Visibility);
}

void APP_PlatformPlayerController::SetWaitingTextVisibility(ESlateVisibility Visibility)
{
    Client_SetWaitingTextVisibility(Visibility);
}

void APP_PlatformPlayerController::Client_SetWaitingTextVisibility_Implementation(ESlateVisibility Visibility)
{
    HUD = HUD ? HUD.Get() : Cast<APP_HUD>(GetHUD());
    if (!HUD) return;

    HUD->SetWaitingTextVisibility(Visibility);
}

void APP_PlatformPlayerController::ToggleInput(bool bEnableInput)
{
    Client_ToggleInput(bEnableInput);
}

void APP_PlatformPlayerController::Client_ToggleInput_Implementation(bool bEnableInput)
{
    if (bEnableInput)
    {
        EnableInput(this);
    }
    else
    {
        DisableInput(this);
    }
}
