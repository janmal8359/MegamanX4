#pragma once
#include "singletonBase.h"
#include "gameNode.h"


class mapManager : public singletonBase<mapManager>
{
private:
	image* back00;
	image* back01;
	image* back02;
	image* back03;
	image* back04;
	image* back05;
	image* back06;
	image* back07;
	image* back08;
	image* back09;
	image* back10;
	
public:
	mapManager() {}
	~mapManager() {}


	HRESULT init();
	void release();
	void update();
	void render();


	void Load();
	void Delete();

};

