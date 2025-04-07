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

    // Crear el componente raíz
    MallaBomba = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBomba"));
    RootComponent = MallaBomba; // Establecer como componente raíz

    // Crear el componente de malla estática y asignarlo al bloque
    ConstructorHelpers::FObjectFinder<UStaticMesh> MallaBombaAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")); // Ruta correcta para la malla
    if (MallaBombaAsset.Succeeded())
    {
        MallaBomba->SetStaticMesh(MallaBombaAsset.Object); // Asignación del modelo al bloque
        MallaBomba->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // Dimensiones del bloque
        MallaBomba->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Ubicación del bloque
    }

    // Asignar el material al bloque
    ConstructorHelpers::FObjectFinder<UMaterial> MaterialBombaAsset(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'")); // Ruta correcta para el material
    if (MaterialBombaAsset.Succeeded())
    {
        MallaBomba->SetMaterial(0, MaterialBombaAsset.Object); // Asignación del material al bloque
    }
    // Habilitar colisiones y fisica
    MallaBomba->SetSimulatePhysics(true);
    MallaBomba->SetNotifyRigidBodyCollision(true); // Habilita eventos de colisión
    MallaBomba->BodyInstance.SetCollisionProfileName("BlockAllDynamic"); // Configuración de colisión

    // Vincular el evento de colisión
    MallaBomba->OnComponentHit.AddDynamic(this, &ABomba::OnHit);

}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
    Super::BeginPlay();

    // Configurar el temporizador para destruir la bomba después de `TiempoParaDestruir` segundos
    GetWorld()->GetTimerManager().SetTimer(
        DestructionTimer,                        // Identificador del temporizador
        this,                                   // Objeto que ejecuta la función
        &ABomba::DestruirBomba,                 // Función que se llamará
        TiempoParaDestruir,                     // Tiempo en segundos
        false                                   // Si el temporizador debe repetirse (false = una sola vez)
    );

    UE_LOG(LogTemp, Warning, TEXT("¡El temporizador para destruir la bomba ha comenzado!"));
}




// Configurar la función de colisión y destrucción con enemigos 
void ABomba::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this) // Verifica que el actor no sea esta misma bomba
    {
        // Comprueba si el actor colisionado es de tipo AEnemigo
        if (OtherActor->IsA(AEnemigo::StaticClass()))
        {
            UE_LOG(LogTemp, Warning, TEXT("¡Bomba colisionó con un Enemigo! Eliminando..."));

            // Destruir al Enemigo
            OtherActor->Destroy();
        }
    }
}

void ABomba::DestruirBomba()
{
    // Mensaje en la consola para depuración
    UE_LOG(LogTemp, Warning, TEXT("¡La bomba se ha destruido!"));

    // Destruir el actor
    Destroy();
}


// Called every frame
void ABomba::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}