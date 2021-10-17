#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;
	float _height;
	float current, max;

	image* _progressBarTop;
	image* _progressBarBottom;

	string top;
	string bottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(string topKey, string bottomKey, int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};

