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
	//�ϴ� ��� ���� ���۰� �ʿ��ϴ� 
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

	//���ۿ� ��� ������ ���ٰŴ�. �̰� �������� ����ߵǰ� ���� ���� bool ���� ���ؼ� fulling -> render�� �ݺ��ҰŴ�.
	void setZorder();

	void swapKey(string* key1, string* key2);

};

