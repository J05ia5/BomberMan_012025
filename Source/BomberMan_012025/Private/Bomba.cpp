#include "Bomba.h"
#include "Enemigo.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"   // Para ConstructorHelpers
#include "Engine/StaticMesh.h"            // Para UStaticMesh
#include "Materials/Material.h"

// Sets default values
ABomba::ABomba()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Crear el componente ra�z
    MallaBomba = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBomba"));
    RootComponent = MallaBomba; // Establecer como componente ra�z

    // Crear el componente de malla est�tica y asignarlo al bloque
    ConstructorHelpers::FObjectFinder<UStaticMesh> MallaBombaAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); // Ruta correcta para la malla
    if (MallaBombaAsset.Succeeded())
    {
        MallaBomba->SetStaticMesh(MallaBombaAsset.Object); // Asignaci�n del modelo al bloque
        MallaBomba->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // Dimensiones del bloque
        MallaBomba->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Ubicaci�n del bloque
    }

    // Asignar el material al bloque
    ConstructorHelpers::FObjectFinder<UMaterial> MaterialBombaAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'")); // Ruta correcta para el material
    if (MaterialBombaAsset.Succeeded())
    {
        MallaBomba->SetMaterial(0, MaterialBombaAsset.Object); // Asignaci�n del material al bloque
    }
    // Habilitar colisiones y fisica
    MallaBomba->SetSimulatePhysics(true);
    MallaBomba->SetNotifyRigidBodyCollision(true); // Habilita eventos de colisi�n
    MallaBomba->BodyInstance.SetCollisionProfileName("BlockAllDynamic"); // Configuraci�n de colisi�n

    // Vincular el evento de colisi�n
    MallaBomba->OnComponentHit.AddDynamic(this, &ABomba::OnHit);

}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
    Super::BeginPlay();

    // Configurar el temporizador para destruir la bomba despu�s de `TiempoParaDestruir` segundos
    GetWorld()->GetTimerManager().SetTimer(
        DestructionTimer,                        // Identificador del temporizador
        this,                                   // Objeto que ejecuta la funci�n
        &ABomba::DestruirBomba,                 // Funci�n que se llamar�
        TiempoParaDestruir,                     // Tiempo en segundos
        false                                   // Si el temporizador debe repetirse (false = una sola vez)
    );

    UE_LOG(LogTemp, Warning, TEXT("�El temporizador para destruir la bomba ha comenzado!"));
}




// Configurar la funci�n de colisi�n y destrucci�n con enemigos 
void ABomba::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this) // Verifica que el actor no sea esta misma bomba
    {
        // Comprueba si el actor colisionado es de tipo AEnemigo
        if (OtherActor->IsA(AEnemigo::StaticClass()))
        {
            UE_LOG(LogTemp, Warning, TEXT("�Bomba colision� con un Enemigo! Eliminando..."));

            // Destruir al Enemigo
            OtherActor->Destroy();
        }
    }
}

void ABomba::DestruirBomba()
{
    // Mensaje en la consola para depuraci�n
    UE_LOG(LogTemp, Warning, TEXT("�La bomba se ha destruido!"));

    // Destruir el actor
    Destroy();
}


// Called every frame
void ABomba::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}