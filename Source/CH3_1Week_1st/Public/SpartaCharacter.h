// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class CH3_1WEEK_1ST_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	float NormalSpeed;
	float SprintSpeed;
	float StrintMultiplier;
public:
	ASpartaCharacter();

public:	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;


protected:

	virtual void SetupPlayerInputComponent(class UInputComponent*) override;

	UFUNCTION()
	void Move(const FInputActionValue& _Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& _Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& _Value);
	UFUNCTION()
	void Look(const FInputActionValue& _Value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& _Value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& _Value);

};
