#pragma once
#include "singletonBase.h"
#include <vector>

#include "inc\fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")

#define D_SOUNDBUFFER_MAX 20
#define D_CHANNELBUFFER_MAX 50
#define D_TOTALBUFFER_MAX D_SOUNDBUFFER_MAX + D_CHANNELBUFFER_MAX

using namespace FMOD;

class soundManager : public singletonBase<soundManager>
{
public:
	struct S_SOUND_INFO
	{
		std::string strKey;
		Sound** ppSound;
	};

	struct S_CHANNEL_INFO
	{
		std::string strKey;
		Channel** ppChannel;
	};

private:
	typedef std::vector<S_SOUND_INFO> vSound;
	typedef std::vector<S_SOUND_INFO>::iterator viSound;
	typedef std::vector<S_CHANNEL_INFO> vChannel;
	typedef std::vector<S_CHANNEL_INFO>::iterator viChannel;

private:
	vSound m_vSounds;
	System* m_pSystem;
	Sound** m_ppSound;
	Channel** m_ppChannel;

public:
	soundManager();
	virtual ~soundManager();

	HRESULT init();
	void release();
	void update();

	void addSound(std::string strSoundKey, const char* pSoundFileName, BOOL bIsBgm, BOOL bIsLoop);
	void play(std::string strSoundKey, float fVolume = 1.F);
	void stop(std::string strSoundKey);
	void pause(std::string strSoundKey);
	void resume(std::string strSoundKey);

	bool isPlaySound(std::string strSoundKey);
	bool isPauseSound(std::string strSoundKey);
};

