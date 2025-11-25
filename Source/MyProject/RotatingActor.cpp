// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"
#include "HealthComponent.h"

// Sets default values
ARotatingActor::ARotatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	RootComponent = DefualtSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMesh->SetupAttachment(DefualtSceneRoot);

	


}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &ARotatingActor::OnComponentHit);
}

void ARotatingActor::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(OtherActor);*/
	UHealthComponent* healthComp = OtherActor->FindComponentByClass<UHealthComponent>();
	if (healthComp) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Damage Player"));
		//Player->TakeDamage(10.f);
		healthComp->TakeDamage(10.f);
		Destroy();
	}
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = FRotator(0.f, RotationSpeed * DeltaTime, 0.f);
	StaticMesh->AddLocalRotation(NewRotation);

}

