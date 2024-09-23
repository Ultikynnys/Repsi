// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointyThing.generated.h"

UCLASS()
class REPSICORE_API APointyThing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointyThing();

	void OnConstruction(const FTransform& Transform);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	// Static Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	// Offset Rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FRotator Offset = FRotator();

	UPROPERTY(ReplicatedUsing=OnUpdateRot,EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FRotator Orientation = FRotator();

	UFUNCTION() void OnUpdateRot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateHudVal();

	UFUNCTION(Server, Reliable)
	void Server_UpdateHudVal();

};
