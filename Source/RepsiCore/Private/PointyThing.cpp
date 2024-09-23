// Fill out your copyright notice in the Description page of Project Settings.
#include "PointyThing.h"
#include "RepsiPawn.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APointyThing::APointyThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetReplicates(true);
    SetReplicateMovement(true);
	NetCullDistanceSquared = FMath::Square(1500.0f);
	// Make our Actor damageable initially, so Weapon traces will deal damage
	SetCanBeDamaged(true);

    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Create the Static Mesh Component
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

    // Attach the Static Mesh Component to the Root Component
    RootComponent = StaticMeshComponent;

}

void APointyThing::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

// Override TakeDamage function
float APointyThing::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    SetOwner(EventInstigator);
    if (HasAuthority())
    {
        
        Multicast_UpdateHudVal();
    }

    // Call the parent class version if you want default behavior
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


    return ActualDamage;
}

void APointyThing::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    

    // Replicate the transform
    DOREPLIFETIME(APointyThing, Orientation);
}

void APointyThing::OnUpdateRot()
{
}

// Called when the game starts or when spawned
void APointyThing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointyThing::Tick(float DeltaTime)
{
    SetActorRotation(Orientation);
	Super::Tick(DeltaTime);

}

void APointyThing::Server_UpdateHudVal_Implementation()
{
    if (HasAuthority())
    {
        Multicast_UpdateHudVal_Implementation();
    }
}

void APointyThing::Multicast_UpdateHudVal_Implementation()
{       
    if (!HasAuthority())
    {

        ARepsiPlayerController* controller = Cast<ARepsiPlayerController>(GetWorld()->GetFirstPlayerController());
        check(controller)
        ARepsiPawn* player = Cast<ARepsiPawn>(controller->GetPawn());
        check(player->CounterHud)
         player->CounterHud->IncrementCounter();

    }
    else
    {
        Orientation = GetOwner()->GetActorRotation() + Offset;
    }
}



