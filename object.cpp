#include "pch.h"
#include "object.h"

HRESULT object::init()
{
	return S_OK;
}

HRESULT object::init(POINT position, int width, int height)
{
	_x = position.x;
	_y = position.y;
	_width = width;
	_height = height;

	CAMERAMANAGER->MakeObject(_rc, _x, _y, _width, _height);

	return S_OK;
}

void object::release()
{
}

void object::update()
{
	//_rc = RectMake(position.x, position.y, width, height);
	CAMERAMANAGER->MakeObject(_rc, _x, _y, _width, _height);
	
}

void object::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
}
