#include "SoundManager.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// 초기화 작업
bool SoundManager::Initialize(UWorld* pWorld)
{
	if (pWorld == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::Initialize - pWorld == nullptr"));
		return false;
	}
	m_wpWorld = pWorld;

	m_wpSoundConcurrency = LoadObject<USoundConcurrency>(nullptr, TEXT(""));
	if (m_wpSoundConcurrency == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::Initialize - m_wpSoundConcurrency == nullptr"));
		return false;
	}

	m_bInitialized = true;
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 해제 작업
void SoundManager::Finalize()
{
	UnLoadSounds();

	m_wpWorld = nullptr;
	m_wpSoundConcurrency = nullptr;

	m_bInitialized = false;
}

//////////////////////////////////////////////////////////////////////////
// 사운드를 재생합니다.
uint64 SoundManager::PlaySound(const FString& strPath, const FVector& vPos)
{
	uint64 nAudioComponentID = 0;

	if (m_bInitialized == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::PlaySound - Initialize Failed, %s"), *strPath);
		return nAudioComponentID;
	}

	UWorld* pWorld = m_wpWorld.Get();
	if (pWorld == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::PlaySound - pWorld == nullptr, %s"), *strPath);
		return nAudioComponentID;
	}

	// 사운드 객체가 없다면 새로 불러옵니다.
	if (LoadSound(strPath) == false)
		return false;

	FAudioDevice* pAudioDevice = pWorld->GetAudioDevice();
	// 오디오 디바이스가 존재하는지?
	if (pAudioDevice == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::PlaySound - pAudioDevice == nullptr, %s"), *strPath);
		return nAudioComponentID;
	}

	// 인자로부터 위치값을 설정하고 있다면 재생되는 사운드 위치를 설정합니다.
	UAudioComponent* pAudioComponent = nullptr;
	if (vPos == FVector::ZeroVector)
		pAudioComponent = UGameplayStatics::SpawnSound2D(pWorld, m_mapSound[strPath], 1.0f, 1.0f, 0.0f, m_wpSoundConcurrency.Get());
	else
		pAudioComponent = UGameplayStatics::SpawnSoundAtLocation(pWorld, m_mapSound[strPath], vPos, FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, m_wpSoundConcurrency.Get());

	if (pAudioComponent != nullptr)
	{
		// 컴포넌트ID를 통해 컨테이너에 추가합니다.
		nAudioComponentID = pAudioComponent->GetAudioComponentID();
		if (m_mapAudioComponents.Contains(nAudioComponentID) == false)
			m_mapAudioComponents.Add(nAudioComponentID, pAudioComponent);
	}
	return nAudioComponentID;
}

//////////////////////////////////////////////////////////////////////////
// 사운드가 재생 중인지 확인합니다.
bool SoundManager::IsPlayingSound(const uint64& nAudioComponentID)
{
	if (m_mapAudioComponents.Contains(nAudioComponentID) == true)
	{
		if (m_mapAudioComponents[nAudioComponentID].IsValid() == true)
			return m_mapAudioComponents[nAudioComponentID]->IsPlaying();
		else
			m_mapAudioComponents.Remove(nAudioComponentID);
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 사운드를 정지시킵니다.
void SoundManager::StopSound(const uint64& nAudioComponentID)
{
	if (m_mapAudioComponents.Contains(nAudioComponentID) == true)
	{
		if (m_mapAudioComponents[nAudioComponentID].IsValid() == true)
			m_mapAudioComponents[nAudioComponentID]->Stop();

		m_mapAudioComponents.Remove(nAudioComponentID);
	}
}

//////////////////////////////////////////////////////////////////////////
// 전체 사운드를 정지시킵니다.
void SoundManager::StopAllSounds()
{
	for (auto audioIter = m_mapAudioComponents.CreateIterator(); audioIter; ++audioIter)
	{
		if (audioIter.Value().IsValid() == true)
			audioIter.Value()->Stop();
	}
	m_mapAudioComponents.Empty();
}

//////////////////////////////////////////////////////////////////////////
// 사운드 객체들을 언로드시킵니다.
void SoundManager::UnLoadSounds()
{
	StopAllSounds();
	m_mapSound.Empty();
}

//////////////////////////////////////////////////////////////////////////
// BGM을 재생합니다.
uint64 SoundManager::PlayBGM(const FString& strPath)
{
	uint64 nAudioComponentID = 0;

	if (m_bInitialized == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::PlayBGM - Initialize Failed, %s"), *strPath);
		return nAudioComponentID;
	}

	return nAudioComponentID;
}

//////////////////////////////////////////////////////////////////////////
// BGM이 재생 중인지 확인합니다.
bool SoundManager::IsPlayingBGM(const uint64& nAudioComponentID)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
// BGM을 정지시킵니다.
void SoundManager::StopBGM(const uint64& nAudioComponentID)
{

}

//////////////////////////////////////////////////////////////////////////
// 사운드 객체를 불러옵니다.
bool SoundManager::LoadSound(const FString& strPath)
{
	if (m_mapSound.Contains(strPath) == false)
	{
		// 사운드를 불러옵니다.
		USoundBase* pSoundBase = LoadObject<USoundBase>(nullptr, *strPath);
		if (pSoundBase == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("SoundManager::PlaySound - pSoundBase == nullptr, %s"), *strPath);
			return false;
		}
		// 가비지 컬렉션 대상에서 제외
		pSoundBase->AddToRoot();

		// 컨테이너를 추가합니다.
		m_mapSound.Add(strPath, pSoundBase);
	}
	return true;
}