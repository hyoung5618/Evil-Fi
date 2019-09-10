#pragma once

// ���带 �����ϴ� �Ŵ����Դϴ�. [9/8/2019 ImTaeJun]

#include "DesignPattern/Singleton.h"
#include "Common/GameType.h"

#include <Engine/World.h>
#include "UnrealString.h"

#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

class SoundManager : public TSingleton<SoundManager>
{
public:
	// �Ŵ��� �ʱ�ȭ, ����
	bool	Initialize(UWorld* pWorld);
	void	Finalize();

	// ����
	uint64	PlaySound(const FString& strPath, const FVector& vPos);
	bool	IsPlayingSound(const uint64& nAudioComponentID);
	void	StopSound(const uint64& nAudioComponentID);
	void	StopAllSounds();
	void	UnLoadSounds();

	// �������
	uint64	PlayBGM(const FString& strPath);
	bool	IsPlayingBGM(const uint64& nAudioComponentID);
	void	StopBGM(const uint64& nAudioComponentID);

private:
	bool	LoadSound(const FString& strPath);

private:
	bool											m_bInitialized = false;				// �ʱ�ȭ ����
	TWeakObjectPtr<UWorld>							m_wpWorld = nullptr;				// ���� ��ü

	TWeakObjectPtr<USoundConcurrency>				m_wpSoundConcurrency = nullptr;		// ���� ���� ��� ������

	TMap<FString, USoundBase*>						m_mapSound;							// ����
	TMap<FString, USoundWave*>						m_mapBGM;							// �������
	TMap<uint64, TWeakObjectPtr<UAudioComponent>>	m_mapAudioComponents;				// ����� ������Ʈ
};