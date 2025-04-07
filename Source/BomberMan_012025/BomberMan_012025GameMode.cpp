// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberMan_012025GameMode.h"
#include "BomberMan_012025Character.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Enemigo.h"
#include "Bomba.h"
#include "Kismet/KismetMathLibrary.h" // Para FMath::RandRange() Calculos
#include "Engine/World.h" // Para GetWorld()
#include "Bloque.h"
#include "BloqueLadrillo.h"
#include "BloqueBurbuja.h"
#include "BloqueMadera.h"
#include "BloqueAcero.h"
#include "BloqueConcreto.h"
#include "BloquePiedra.h"
#include "BloqueCeramica.h"
#include "BloqueArena.h"
#include "BloqueVidrio.h"
#include "BloqueCesped.h"

ABomberMan_012025GameMode::ABomberMan_012025GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// Asignar la clase de la bomba
	ClaseBomba = ABomba::StaticClass();


	// Habilitar actualización periódica para el Game Mode
	PrimaryActorTick.bCanEverTick = true;
}

void ABomberMan_012025GameMode::Tick(float DeltaSeconds)
{
}

void ABomberMan_012025GameMode::BeginPlay()
{
	// Llamar a la función para spawnear enemigos
	SpawnEnemigo();
	
	Super::BeginPlay(); 

	// Vincular la tecla para spawnear
	APlayerController* Controlador = GetWorld()->GetFirstPlayerController();
	if (Controlador)
	{
		Controlador->InputComponent->BindAction("SpawnBomba", IE_Pressed, this, &ABomberMan_012025GameMode::SpawnBomba);
	}

	GEngine->AddOnScreenDebugMessage(-1, -1.f, FColor::Red, TEXT("Cargando el juego"));
	
	for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
	{
		for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
		{
			int32 valor = aMapaBloques[fila][columna];
			if (valor != 0)
			{
				FVector posicionBloque = FVector(XInicial + columna * AnchoBloque, YInicial + fila * LargoBloque, 0.0f);
				SpawnBloque(posicionBloque, valor);
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimer(tHDestruirBloques, this, &ABomberMan_012025GameMode::DestruirBloque, 2.0f, false);
}

void ABomberMan_012025GameMode::SpawnEnemigo()
{
	//Spawnear "n" enemigos
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemigos spawneados"));

	// Establecer una posición base inicial para el primer enemigo
	FVector BaseLocation = FVector(2450.0f, 2550.0f, 10.0f);

	FRotator Rotation = FRotator::ZeroRotator; // Rotación inicial

	// Generar los enemigos
	for (int i = 0; i < 5; i++)
	{
		// Desviación aleatoria en el rango  unidades para X y Y
		float RandomOffsetX = FMath::RandRange(-1950.0f, 1950.0f);
		float RandomOffsetY = FMath::RandRange(-1950.0f, 1950.0f);
		// Calcular la nueva ubicación basada en la última ubicación
		FVector NewLocation = BaseLocation + FVector(RandomOffsetX, RandomOffsetY, 0.0f);
		// Spawn del enemigo
		AEnemigo* NewEnemigo = GetWorld()->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), NewLocation, Rotation);

		// Verificar si el enemigo fue creado y agregarlo al TArray
		if (NewEnemigo) //NewEnemigo generador de enemigos 
		{
			EnemigoArray.Add(NewEnemigo);//guardado en TArrayEnemigo
		}

	}
}

void ABomberMan_012025GameMode::SpawnBomba()
{
	if (ClaseBomba && GetWorld())
	{
		// Obtener el personaje controlado
		ABomberMan_012025Character* Personaje = Cast<ABomberMan_012025Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Personaje)
		{
			// Obtener la posición y la orientación del personaje
			FVector PosicionPersonaje = Personaje->GetActorLocation();
			FRotator RotacionPersonaje = Personaje->GetActorRotation();

			// Calcular la ubicación delante del personaje
			FVector DireccionFrente = RotacionPersonaje.Vector(); // Vector hacia adelante
			FVector UbicacionSpawn = PosicionPersonaje + (DireccionFrente * 200.0f); // Ajusta la distancia (200.0f en este caso)

			// Rotación para la bomba (opcional, puede ser igual a la del personaje)
			FRotator RotacionSpawn = RotacionPersonaje;

			// Spawnear la bomba
			AActor* BombaSpawneada = GetWorld()->SpawnActor<AActor>(ClaseBomba, UbicacionSpawn, RotacionSpawn);
			if (BombaSpawneada)
			{
				UE_LOG(LogTemp, Warning, TEXT("¡Bomba spawneada frente al personaje en %s!"), *UbicacionSpawn.ToString());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ClaseBomba no está configurada."));
	}
}

void ABomberMan_012025GameMode::SpawnBloque(FVector posicionBloque, int32 tipoBloque)
{
	ABloque* BloqueGenerado = nullptr;
	// elegir tipo de bloque basado en el valor
	if (tipoBloque == 10)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueBurbuja>(ABloqueBurbuja::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 9)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueAcero>(ABloqueAcero::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 8)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueConcreto>(ABloqueConcreto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 7)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueLadrillo>(ABloqueLadrillo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 6)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueMadera>(ABloqueMadera::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 5)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloquePiedra>(ABloquePiedra::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 4)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueCeramica>(ABloqueCeramica::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 3)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueArena>(ABloqueArena::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 2)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueVidrio>(ABloqueVidrio::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (tipoBloque == 1)
	{
		BloqueGenerado = GetWorld()->SpawnActor<ABloqueCesped>(ABloqueCesped::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
	}
	else {
		return;
	}
	// Agregar el bloque generado al Tarray
	if (BloqueGenerado)
	{
		aBloques.Add(BloqueGenerado);
	}
}

//desetruir bloques
void ABomberMan_012025GameMode::DestruirBloque()
{
	//Seleccionar aleatoriamente un bloque del array ABloques para su eliminacion
	int numeroBloques = aBloques.Num();
	int NumeroAleatorio = FMath::RandRange(1, numeroBloques);

	if (aBloques.Num() > 0)
	{
		BloqueActual = aBloques[NumeroAleatorio]; // Obtén el primer bloque
		if (BloqueActual)
		{
			BloqueActual->Destroy();
			// Realiza operaciones con el bloque
			//primerBloque->SetActorLocation(FVector(100.0f, 100.0f, 100.0f));
		}
	}
}

