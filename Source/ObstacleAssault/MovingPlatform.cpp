// Proje ayarlarının açıklama sayfasındaki telif hakkı notlarını doldurun.

#include "MovingPlatform.h"

// Varsayılan değerleri ayarlar.
AMovingPlatform::AMovingPlatform()
{
 	// Tick() fonksiyonunun her karede çağrılmasını sağlar. Performans gerekirse devre dışı bırakılabilir.
	PrimaryActorTick.bCanEverTick = true;
}

// Oyun başladığında veya aktör oluşturulduğunda çağrılır.
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Aktörün başlangıç konumunu kaydetmek için kullanılır.
	StartLocation = GetActorLocation();

	// Aktörün adını bir debug logu ile yazdırır.
	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Her karede çağrılan işlev.
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Platformun hareketini kontrol eder.
	MovePlatform(DeltaTime);

	// Platformun rotasyonunu kontrol eder.
	RotatePlatform(DeltaTime);
}

// Platformun hareket etmesini sağlayan işlev.
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Platformun başlangıç konumuna dönmesi gerekip gerekmediğini kontrol eder.
	if (ShouldPlatformReturn())
	{
		// Hareket yönünü normalize eder ve başlangıç konumunu günceller.
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += (MoveDirection * MovedDistance);

		// Platformu başlangıç konumuna geri taşır.
		SetActorLocation(StartLocation);

		// Platformun hızını tersine çevirerek geri dönüş sağlar.
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{ 
		// Platformun mevcut konumunu alır ve yeni konumunu hesaplar.
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += (PlatformVelocity * DeltaTime);

		// Yeni konumu aktöre uygular.
		SetActorLocation(CurrentLocation);
	}
}

// Platformun rotasyonunu gerçekleştiren işlev.
void AMovingPlatform::RotatePlatform(float DT)
{
	// Platformun mevcut rotasyonuna, tanımlı rotasyon hızını ekler.
	AddActorLocalRotation(RotationVelocity * DT);
}

// Platformun başlangıç konumuna geri dönüp dönmemesi gerektiğini kontrol eder.
bool AMovingPlatform::ShouldPlatformReturn() const
{
	// Platformun taşındığı mesafeyi kontrol eder ve maksimum mesafeyi aşıp aşmadığını döndürür.
	return GetDistanceMoved() > MovedDistance;
}

// Platformun başlangıç konumundan ne kadar uzaklaştığını hesaplayan işlev.
float AMovingPlatform::GetDistanceMoved() const
{
	// Başlangıç konumu ile mevcut konum arasındaki mesafeyi döndürür.
	return FVector::Dist(StartLocation, GetActorLocation());
}
