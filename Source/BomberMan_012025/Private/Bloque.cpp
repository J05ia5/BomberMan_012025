#include "Bloque.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABloque::ABloque()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
	RootComponent = MallaBloque;
	//MallaBloque->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjetoMallaBloque(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (ObjetoMallaBloque.Succeeded())
	{
		MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);

		MallaBloque->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); //la posicion del bloque

		MallaBloque->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f)); //la escala del bloque
	}

	FloatSpeed = 5.0f; 
	RotationSpeed = 3.0f;

	bPuedeMoverse = FMath::RandBool();
}

// Called when the game starts or when spawned
void ABloque::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}