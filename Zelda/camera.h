#pragma once
#include "image.h"
#include "gameNode.h"

class camera : public gameNode
{
private:
	float _cameraX;
	float _cameraY;
	float _startX;
	float _startY;

	int _mapWidth;
	int _mapHeight;

public:
	camera();
	~camera();

	HRESULT init();
	void release();
	void update(int mapWidth, int mapHeight);
	void render();

	void resetCamera();

	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }
	float getStartX() { return _startX; }
	float getStartY() { return _startY; }

	void setCameraX(float cameraX) { _cameraX = cameraX; }
	void setCameraY(float cameraY) { _cameraY = cameraY; }
	void setStartX(float startX) { _startX = startX; }
	void setStartY(float startY) { _startY = startY; }

	void drawCameraPos();

	bool isCameraXEndSide();
	bool isCameraXZeroSide();

	bool isCameraYEndSide();
	bool isCameraYZeroSide();
};

