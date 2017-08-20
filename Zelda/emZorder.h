#pragma once
#include "gameNode.h"
#include <vector>

class enemyManager;
class enemy;
class player;


class emZorder : public gameNode
{
public:
	struct S_BUFFER_INFO
	{
		std::string strDataKey;
		void* pV;
	};

private:
	//일단 모두 담을 버퍼가 필요하다 
	typedef std::vector<S_BUFFER_INFO> vBuffer;
	typedef std::vector<S_BUFFER_INFO>::iterator viBuffer;

private:
	enemyManager* m_pEm;
	player* m_pPlayer;

private:
	vBuffer m_vBuffer;
	viBuffer m_viBuffer;

private:
	bool m_bIsBufferFull;

private:
	void drawZorder();
	void sortZorder();
	void swapZorder(void** pVDst, void** pVSrc);
	void findZorderDataKey(std::string strKeyFst, std::string strKeySec, int nIdx, float* fDstY, float* fSrcY);

public:
	emZorder();
	virtual ~emZorder();

	virtual HRESULT init(enemyManager* em, player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	//버퍼에 담는 역할을 해줄거다. 이건 업뎃에서 해줘야되고 또한 나는 bool 값을 통해서 fulling -> render을 반복할거다.
	void setZorder();

	void swapKey(string* key1, string* key2);

};

