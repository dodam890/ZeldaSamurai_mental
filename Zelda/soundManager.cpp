#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager() :
	m_ppChannel(NULL),
	m_ppSound(NULL),
	m_pSystem(NULL)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	System_Create(&m_pSystem);
	m_pSystem->init(D_TOTALBUFFER_MAX, FMOD_INIT_NORMAL, NULL);

	m_ppSound = new Sound*[D_TOTALBUFFER_MAX]();
	m_ppChannel = new Channel*[D_TOTALBUFFER_MAX]();

	memset(m_ppSound, 0, sizeof(Sound*) * D_TOTALBUFFER_MAX);
	memset(m_ppChannel, 0, sizeof(Sound*) * D_TOTALBUFFER_MAX);
	return S_OK;
}

void soundManager::release()
{
	if (m_ppChannel || m_ppSound)
	{
		for (int i = 0; i < D_TOTALBUFFER_MAX; i++)
		{
			if (m_ppChannel) m_ppChannel[i]->stop();
			if (m_ppSound) m_ppSound[i]->release();
		}
	}

	SAFE_DELETE_ARRAY(m_ppChannel);
	SAFE_DELETE_ARRAY(m_ppSound);

	viSound del = m_vSounds.begin();
	for (del; del != m_vSounds.end(); del++)
	{
		m_vSounds.erase(del);
	}

	if (m_pSystem)
	{
		m_pSystem->release();
		m_pSystem->close();
	}
}

void soundManager::update()
{
	m_pSystem->update();
}

void soundManager::addSound(std::string strSoundKey, const char * pSoundFileName, BOOL bIsBgm, BOOL bIsLoop)
{

	if (bIsLoop)
	{
		if (bIsBgm)
		{
			m_pSystem->createStream(pSoundFileName, FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_vSounds.size()]);
		}
		else
		{
			m_pSystem->createSound(pSoundFileName, FMOD_LOOP_NORMAL, NULL, &m_ppSound[m_vSounds.size()]);
		}
	}
	else
	{
		if (bIsBgm)
		{
			m_pSystem->createStream(pSoundFileName, FMOD_DEFAULT, NULL, &m_ppSound[m_vSounds.size()]);
		}
		else
		{
			m_pSystem->createSound(pSoundFileName, FMOD_DEFAULT, NULL, &m_ppSound[m_vSounds.size()]);
		}
	}

	S_SOUND_INFO sSound = { strSoundKey, &m_ppSound[m_vSounds.size()] };
	m_vSounds.push_back(sSound);
}

void soundManager::play(std::string strSoundKey, float fVolume)
{
	int nCurIdx = 0;

	viSound find = m_vSounds.begin();
	for (find; find != m_vSounds.end(); find++, nCurIdx++)
	{
		if (find->strKey == strSoundKey)
		{
			m_pSystem->playSound(FMOD_CHANNEL_FREE, m_ppSound[nCurIdx], false, &m_ppChannel[nCurIdx]);
			m_ppChannel[nCurIdx]->setVolume(fVolume);
			break;
		}
	}
}

void soundManager::stop(std::string strSoundKey)
{
	int nCurIdx = 0;

	viSound find = m_vSounds.begin();
	for (find; find != m_vSounds.end(); find++, nCurIdx++)
	{
		if (find->strKey == strSoundKey)
		{
			m_ppChannel[nCurIdx]->stop();
			break;
		}
	}
}

void soundManager::pause(std::string strSoundKey)
{
	int nCurIdx = 0;

	viSound find = m_vSounds.begin();
	for (find; find != m_vSounds.end(); find++, nCurIdx++)
	{
		if (find->strKey == strSoundKey)
		{
			m_ppChannel[nCurIdx]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(std::string strSoundKey)
{
	int nCurIdx = 0;

	viSound find = m_vSounds.begin();
	for (find; find != m_vSounds.end(); find++, nCurIdx++)
	{
		if (find->strKey == strSoundKey)
		{
			m_ppChannel[nCurIdx]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(std::string strSoundKey)
{
	int nCurIdx = 0;
	bool bIsPlaySound = false;

	viSound find = m_vSounds.begin();
	for (find; find != m_vSounds.end(); find++, nCurIdx++)
	{
		if (find->strKey == strSoundKey)
		{
			m_ppChannel[nCurIdx]->isPlaying(&bIsPlaySound);
			break;
		}
	}
	return bIsPlaySound;
}

bool soundManager::isPauseSound(std::string strSoundKey)
{
	int nCurIdx = 0;
	bool bIsPauseSound = false;

	viSound find = m_vSounds.begin();
	for (find; find != m_vSounds.end(); find++, nCurIdx++)
	{
		if (find->strKey == strSoundKey)
		{
			m_ppChannel[nCurIdx]->getPaused(&bIsPauseSound);
			break;
		}
	}
	return bIsPauseSound;
}
