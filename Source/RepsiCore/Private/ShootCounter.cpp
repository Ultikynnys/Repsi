// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootCounter.h"

 void UShootCounter::NativeConstruct()
{
	 Super::NativeConstruct();
	 UE_LOG(LogTemp, Warning, TEXT("UI_INIT"));
	Counter->SetText(IntToFText(count));
}

void UShootCounter::IncrementCounter()
{
	count = count +1;
	Counter->SetText(IntToFText(count));
}

FText IntToFText(int32 Num) {
	FString FormattedNum = FString::Printf(TEXT("%d"), Num);
	return FText::FromString(FormattedNum);
}