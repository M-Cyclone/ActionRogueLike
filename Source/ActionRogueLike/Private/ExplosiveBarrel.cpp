// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnMeshHit);
	StaticMeshComponent->SetupAttachment(RootComponent);

	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComponent->ImpulseStrength = 1000.0f;
	RadialForceComponent->Radius = 800.0f;
	RadialForceComponent->Falloff = RIF_Constant;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}

