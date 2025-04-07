#include "Enemigo.h" // Archivo base de tu clase
#include "GameFramework/CharacterMovementComponent.h" // Para movimientos del personaje
#include "Math/UnrealMathUtility.h" // Para FMath::RandRange()
#include "Engine/World.h" // Para GetWorld()
#include "DrawDebugHelpers.h" // Para dibujar líneas de depuración
#include "Engine/StaticMesh.h"            // Para UStaticMesh
#include "Materials/Material.h"


// Sets default values
AEnemigo::AEnemigo()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Crear el componente raíz
	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo; // Establecer como componente raíz

	// Crear el componente de malla estática y asignarlo al bloque
	ConstructorHelpers::FObjectFinder<UStaticMesh> MallaEnemigoAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'")); // Ruta correcta para la malla
	if (MallaEnemigoAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaEnemigoAsset.Object); // Asignación del modelo al bloque
		MallaEnemigo->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // Dimensiones del bloque
		MallaEnemigo->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Ubicación del bloque
	}

	// Asignar el material al bloque
	ConstructorHelpers::FObjectFinder<UMaterial> MaterialEnemigoAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'")); // Ruta correcta para el material
	if (MaterialEnemigoAsset.Succeeded())
	{
		MallaEnemigo->SetMaterial(0, MaterialEnemigoAsset.Object); // Asignación del material al bloque
	}
	// Configuración del movimiento del enemigo
	MallaEnemigo->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

	//movimiento para enemigo
	DistanciaRecorrida = 0.0f;
}


// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	// Iniciar el movimiento aleatorio
	CambiarDireccion();
}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Detectar obstáculos
	FVector NuevaPosicion = GetActorLocation() + (MovimientoActual * DeltaTime * 200.0f);
	if (DetectarObstaculo(NuevaPosicion))
	{
		CambiarDireccion();
	}
	else
	{
		SetActorLocation(NuevaPosicion);
		DistanciaRecorrida += (MovimientoActual * DeltaTime * 200.0f).Size();

		if (DistanciaRecorrida >= DistanciaMaxima)
		{
			CambiarDireccion();
			DistanciaRecorrida = 0.0f;
		}
	}
}

void AEnemigo::CambiarDireccion()
{
	// Generar un vector de direccion aleatorio
	float RandomX = FMath::RandRange(-1.0f, 1.0f);
	float RandomY = FMath::RandRange(-1.0f, 1.0f);
	MovimientoActual = FVector(RandomX, RandomY, 0.0f).GetSafeNormal();
}

bool AEnemigo::DetectarObstaculo(FVector Destino)
{
	FHitResult HitResult;
	FVector Inicio = GetActorLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//Trazar un rayo para detectar obstaculos
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Inicio, Destino, ECollisionChannel::ECC_WorldStatic, Params);

	//dibuja el rayo en el mundo para depuracion
	DrawDebugLine(GetWorld(), Inicio, Destino, FColor::Green, false, 2.0f, 2.0f, 2.0f);

	// Si se detecta un obstáculo, cambiar la dirección	
	return bHit;
}

// Called to bind functionality to input
void AEnemigo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}