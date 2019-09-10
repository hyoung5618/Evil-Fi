#include "SoundManager.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// �ʱ�ȭ �۾�
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
// ���� �۾�
void SoundManager::Finalize()
{
	UnLoadSounds();

	m_wpWorld = nullptr;
	m_wpSoundConcurrency = nullptr;

	m_bInitialized = false;
}

//////////////////////////////////////////////////////////////////////////
// ���带 ����մϴ�.
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

	// ���� ��ü�� ���ٸ� ���� �ҷ��ɴϴ�.
	if (LoadSound(strPath) == false)
		return false;

	FAudioDevice* pAudioDevice = pWorld->GetAudioDevice();
	// ����� ����̽��� �����ϴ���?
	if (pAudioDevice == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SoundManager::PlaySound - pAudioDevice == nullptr, %s"), *strPath);
		return nAudioComponentID;
	}

	// ���ڷκ��� ��ġ���� �����ϰ� �ִٸ� ����Ǵ� ���� ��ġ�� �����մϴ�.
	UAudioComponent* pAudioComponent = nullptr;
	if (vPos == FVector::ZeroVector)
		pAudioComponent = UGameplayStatics::SpawnSound2D(pWorld, m_mapSound[strPath], 1.0f, 1.0f, 0.0f, m_wpSoundConcurrency.Get());
	else
		pAudioComponent = UGameplayStatics::SpawnSoundAtLocation(pWorld, m_mapSound[strPath], vPos, FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, m_wpSoundConcurrency.Get());

	if (pAudioComponent != nullptr)
	{
		// ������ƮID�� ���� �����̳ʿ� �߰��մϴ�.
		nAudioComponentID = pAudioComponent->GetAudioComponentID();
		if (m_mapAudioComponents.Contains(nAudioComponentID) == false)
			m_mapAudioComponents.Add(nAudioComponentID, pAudioComponent);
	}
	return nAudioComponentID;
}

//////////////////////////////////////////////////////////////////////////
// ���尡 ��� ������ Ȯ���մϴ�.
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
// ���带 ������ŵ�ϴ�.
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
// ��ü ���带 ������ŵ�ϴ�.
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
// ���� ��ü���� ��ε��ŵ�ϴ�.
void SoundManager::UnLoadSounds()
{
	StopAllSounds();
	m_mapSound.Empty();
}

//////////////////////////////////////////////////////////////////////////
// BGM�� ����մϴ�.
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
// BGM�� ��� ������ Ȯ���մϴ�.
bool SoundManager::IsPlayingBGM(const uint64& nAudioComponentID)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
// BGM�� ������ŵ�ϴ�.
void SoundManager::StopBGM(const uint64& nAudioComponentID)
{

}

//////////////////////////////////////////////////////////////////////////
// ���� ��ü�� �ҷ��ɴϴ�.
bool SoundManager::LoadSound(const FString& strPath)
{
	if (m_mapSound.Contains(strPath) == false)
	{
		// ���带 �ҷ��ɴϴ�.
		USoundBase* pSoundBase = LoadObject<USoundBase>(nullptr, *strPath);
		if (pSoundBase == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("SoundManager::PlaySound - pSoundBase == nullptr, %s"), *strPath);
			return false;
		}
		// ������ �÷��� ��󿡼� ����
		pSoundBase->AddToRoot();

		// �����̳ʸ� �߰��մϴ�.
		m_mapSound.Add(strPath, pSoundBase);
	}
	return true;
}