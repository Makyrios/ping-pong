// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "PP_PlatformPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class APP_HUD;
struct FInputActionValue;

UCLASS()
class PINGPONG_API APP_PlatformPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    void BlendCameraView(AActor* CameraActorToBlend);
    
    void UpdatePawnTransform(const FTransform& NewPawnTransform);

    UFUNCTION()
    void UpdateScore(int BlueScore, int RedScore);

    void SetScoreWidgetVisibility(ESlateVisibility Visibility);
    
    void SetWaitingTextVisibility(ESlateVisibility Visibility);

    void ToggleInput(bool bEnableInput);

protected:
    virtual void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
    
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    virtual void OnPossess(APawn* InPawn) override;

    void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);

private:
    UFUNCTION(Client, Reliable)
    void Client_BlendCameraView(AActor* CameraActorToBlend);
    
    UFUNCTION(Client, Reliable)
    void Client_UpdateScore(int BlueScore, int RedScore);

    UFUNCTION(Client, Reliable)
    void Client_SetScoreWidgetVisibility(ESlateVisibility Visibility);

    UFUNCTION(Client, Reliable)
    void Client_SetWaitingTextVisibility(ESlateVisibility Visibility);
    
    UFUNCTION(Client, Reliable)
    void Client_ToggleInput(bool bEnableInput);
    
private:
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;
    
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveForwardAction;
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveRightAction;

    UPROPERTY(Replicated)
    TObjectPtr<APawn> PlayerPawn;

    UPROPERTY()
    TObjectPtr<APP_HUD> HUD;
};
