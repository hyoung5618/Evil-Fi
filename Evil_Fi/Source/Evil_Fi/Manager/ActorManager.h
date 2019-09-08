#include "DesignPattern/Singleton.h"
#include "Common/GameType.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>

class ActorManager : public TSingleton<ActorManager>
{
public:

	template<typename T>
	bool CreateActor(UWorld* pWorld, FName strName, const FVector& Location, const FRotator& Rotation)
	{
		if (pWorld == nullptr)
			return false;

		FActorSpawnParameters SPAWNPARAMETER;
		SPAWNPARAMETER.Name = strName;
		AActor* pActor = pWorld->SpawnActor<T>(Location, Rotation, SPAWNPARAMETER);

		if (pActor) {
			TArray<TSharedPtr<AActor>>* pArrActor = m_mapActorArry.Find(strName);
			if (pArrActor == nullptr)
			{
				TArray<TSharedPtr<AActor>> arrActor;
				arrActor.Add(MakeShareable(pActor));
				m_mapActorArry.Emplace(strName, arrActor);
			}
			else
			{
				pArrActor->Add(MakeShareable(pActor));
			}
			return true;
		}

		return false;
	}

	void DeleteActor()
	{

	}

	void FindActor()
	{

	}

	void LoopActor()
	{

	}

private:
	TMap<FName, TArray<TSharedPtr<AActor>>> m_mapActorArry;
};