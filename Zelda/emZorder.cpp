#include "stdafx.h"
#include "emZorder.h"
#include "enemyManager.h"
#include "enemy.h"
#include "player.h"

emZorder::emZorder() :
	m_bIsBufferFull(false)
{
}

emZorder::~emZorder()
{
}

HRESULT emZorder::init(enemyManager* em, player* player)
{
	m_pEm = em;
	m_pPlayer = player;

	m_vBuffer.reserve(100);

	return S_OK;
}

void emZorder::release()
{
}

void emZorder::update()
{
	setZorder();
}

void emZorder::render()
{
	drawZorder();
}

void emZorder::setZorder()
{
	if (m_vBuffer.size() != 0)
	{
		for (int i = 0; i < m_vBuffer.size(); i++)
		{
			m_vBuffer.erase(m_vBuffer.begin() + i);
		}
		m_vBuffer.clear();
	}

	vector<enemy*>& vEm = m_pEm->getVEnemy();
	S_BUFFER_INFO sBuffer = {};

	for (int i = 0; i < vEm.size(); i++)
	{
		sBuffer = { "enemy", vEm[i] };
		m_vBuffer.push_back(sBuffer);
	}

	sBuffer = { "player", m_pPlayer };
	m_vBuffer.push_back(sBuffer);

	sortZorder();
}

void emZorder::swapKey(string* key1, string* key2)
{
	string key = *key1;
	*key1 = *key2;
	*key2 = key;
}

void emZorder::drawZorder()
{
	for (int i = 0; i < m_vBuffer.size(); i++)
	{
		if (m_vBuffer[i].strDataKey == "enemy")
		{
			((enemy*)m_vBuffer[i].pV)->render();
		}
		else
		{
			((player*)m_vBuffer[i].pV)->render();
		}
	}
}

void emZorder::sortZorder()
{
	float fDstCenY = 0;
	float fSrcCenY = 0;

	for (int i = 0; i < m_vBuffer.size() - 1; i++)
	{
		for (int j = 0; j < m_vBuffer.size() - 1; j++)
		{
			findZorderDataKey(m_vBuffer[j].strDataKey, m_vBuffer[j + 1].strDataKey, j, &fDstCenY, &fSrcCenY);

			if (fDstCenY >= fSrcCenY)
			{
				swapZorder(&m_vBuffer[j].pV, &m_vBuffer[j + 1].pV);
				//swapKey(&m_vBuffer[j].strDataKey, &m_vBuffer[j + 1].strDataKey);
			}
		}
	}
}

void emZorder::swapZorder(void** pVDst, void** pVSrc)
{
	void* pVTmp = (*pVDst);
	(*pVDst) = (*pVSrc);
	(*pVSrc) = pVTmp;
}

void emZorder::findZorderDataKey(std::string strKeyFst, std::string strKeySec, int nIdx, float* fDstY, float* fSrcY)
{
	if (strKeyFst == "enemy" && strKeySec == "player")
	{
		(*fDstY) = ((enemy*)m_vBuffer[nIdx].pV)->getCenterY();
		(*fSrcY) = ((player*)m_vBuffer[nIdx + 1].pV)->getCenterY();
	}
	else if (strKeyFst == "player" && strKeySec == "enemy")
	{
		(*fDstY) = ((player*)m_vBuffer[nIdx].pV)->getCenterY();
		(*fSrcY) = ((enemy*)m_vBuffer[nIdx + 1].pV)->getCenterY();
	}
	else if (strKeyFst == "enemy" && strKeySec == "enemy")
	{
		(*fDstY) = ((enemy*)m_vBuffer[nIdx].pV)->getCenterY();
		(*fSrcY) = ((enemy*)m_vBuffer[nIdx + 1].pV)->getCenterY();
	}
}
