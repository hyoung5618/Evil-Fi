#pragma once

// 사운드를 관리하는 매니저입니다. [9/8/2019 ImTaeJun]

#include "DesignPattern/Singleton.h"
#include "Common/GameType.h"

#include <Engine/World.h>
#include "UnrealString.h"

#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

class SoundManager : public TSingleton<SoundManager>
{
public:
	// 매니저 초기화, 해제
	bool	Initialize(UWorld* pWorld);
	void	Finalize();

	// 사운드
	uint64	PlaySound(const FString& strPath, const FVector& vPos);
	bool	IsPlayingSound(const uint64& nAudioComponentID);
	void	StopSound(const uint64& nAudioComponentID);
	void	StopAllSounds();
	void	UnLoadSounds();

	// 배경음악
	uint64	PlayBGM(const FString& strPath);
	bool	IsPlayingBGM(const uint64& nAudioComponentID);
	void	StopBGM(const uint64& nAudioComponentID);

private:
	bool	LoadSound(const FString& strPath);

private:
	bool											m_bInitialized = false;				// 초기화 상태
	TWeakObjectPtr<UWorld>							m_wpWorld = nullptr;				// 월드 객체

	TWeakObjectPtr<USoundConcurrency>				m_wpSoundConcurrency = nullptr;		// 사운드 동시 재생 데이터

	TMap<FString, USoundBase*>						m_mapSound;							// 사운드
	TMap<FString, USoundWave*>						m_mapBGM;							// 배경음악
	TMap<uint64, TWeakObjectPtr<UAudioComponent>>	m_mapAudioComponents;				// 오디오 컴포넌트
};