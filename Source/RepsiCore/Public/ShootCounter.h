// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ShootCounter.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class REPSICORE_API UShootCounter : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;
	void IncrementCounter();

	UPROPERTY(EditAnywhere,meta=(BindWidget))
	class UTextBlock* Counter;

	UPROPERTY()
	int count = 0;
};

FText IntToFText(int32 Num);
