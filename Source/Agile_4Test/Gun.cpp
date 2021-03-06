// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	
	SetRootComponent(Root);
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You’ve been shot!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr){return;}

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr){return;}

	FVector Location;
	FRotator Rotation; 
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if(bSuccess)
	{
		DrawDebugPoint(GetWorld(), Location, 20, FColor::Red, true);
	}
}
