#include "pch.h"
#include "objectManager.h"

HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	for (_viCollider = _vCollider.begin(); _viCollider != _vCollider.end(); ++_viCollider)
	{
		(*_viCollider)->update();
	}
}

void objectManager::render()
{
	for (_viCollider = _vCollider.begin(); _viCollider != _vCollider.end(); ++_viCollider)
	{
		(*_viCollider)->render();
	}
}

void objectManager::setCollider()
{
	object* coll[COLLMAX];
	for (int i = 0; i < COLLMAX; i++) coll[i] = new collider;

	coll[0]->init(PointMake(0, 680), 800, 200);            // 0, 680 - 800, 200
	_vCollider.push_back(coll[0]);
	coll[1]->init(PointMake(800, 630), 400, 200);		   // 800, 630 - 400, 200
	_vCollider.push_back(coll[1]);
	coll[2]->init(PointMake(1200, 680), 200, 200);		   // 1200, 680 - 200, 200
	_vCollider.push_back(coll[2]);
	coll[3]->init(PointMake(1600, 580), 400, 150);		   // 1600, 580 - 400, 200
	_vCollider.push_back(coll[3]);
	coll[4]->init(PointMake(1600, 210), 400, 150);		   // 1600, 210 - 400, 200
	_vCollider.push_back(coll[4]);

	coll[5]->init(PointMake(2310, 690), 100, 200);		   // 2310, 690 - 100, 200
	_vCollider.push_back(coll[5]);
	coll[6]->init(PointMake(3010, 525), 200, 100);		   // 3010, 525 - 200, 100
	_vCollider.push_back(coll[6]);

	coll[7]->init(PointMake(3510, 370), 200, 150);		   // 3510, 370 | 690 - 200 
	_vCollider.push_back(coll[7]);
	coll[8]->init(PointMake(3510, 690), 200, 150);
	_vCollider.push_back(coll[8]);
	coll[9]->init(PointMake(3920, 210), 200, 150);		   // 3920, 210 | 530 - 200
	_vCollider.push_back(coll[9]);
	coll[10]->init(PointMake(3920, 530), 200, 150);		   
	_vCollider.push_back(coll[10]);
	coll[11]->init(PointMake(4315, 370), 200, 150);		   // 4315, 370 - 200
	_vCollider.push_back(coll[11]);
	coll[12]->init(PointMake(4515, 475), 200, 150);		   // 4515, 575 - 200
	_vCollider.push_back(coll[12]);
	coll[13]->init(PointMake(5315, 315), 200, 150);		   // 5315, 315 - 200
	_vCollider.push_back(coll[13]);
	coll[14]->init(PointMake(5515, 265), 200, 150);		   // 5515, 265 - 200
	_vCollider.push_back(coll[14]);
	coll[15]->init(PointMake(5625, 700), 3550, 150);	   // 5625, 700 - 3550
	_vCollider.push_back(coll[15]);
	coll[16]->init(PointMake(6015, 0), 3160, 160);		   // 6015, 160 - 3160
	_vCollider.push_back(coll[16]);
	coll[17]->init(PointMake(6425, 595), 140, 200);		   // 6425, 595 - 140
	_vCollider.push_back(coll[17]);
	coll[18]->init(PointMake(6975, 540), 140, 200);		   // 6975, 540 - 140
	_vCollider.push_back(coll[18]);
	coll[19]->init(PointMake(7525, 540), 140, 200);		   // 7525, 540 - 140
	_vCollider.push_back(coll[19]);
	coll[20]->init(PointMake(7875, 590), 140, 200);		   // 7875, 590 - 140
	_vCollider.push_back(coll[20]);
	coll[21]->init(PointMake(8775, 540), 400, 200);		   // 8775, 540 - 400
	_vCollider.push_back(coll[21]);
	coll[22]->init(PointMake(6015, 0), 555, 320);		   // 6015, 0 - 555, 320
	_vCollider.push_back(coll[22]);
	coll[23]->init(PointMake(8225, 0), 155, 325);		   // 8225, 0 - 155, 325
	_vCollider.push_back(coll[23]);
	coll[24]->init(PointMake(8775, 0), 400, 325);		   // 8775, 0 - 400, 325
	_vCollider.push_back(coll[24]);
	coll[25]->init(PointMake(9430, 210), 300, 120);		   // 9430, 210 - 300, 120
	_vCollider.push_back(coll[25]);
	coll[26]->init(PointMake(9425, 690), 300, 200);		   // 9425, 690 - 300
	_vCollider.push_back(coll[26]);
	coll[27]->init(PointMake(9625, 210), 110, 590);		   // 9625, 210 - 110, 590
	_vCollider.push_back(coll[27]);
	coll[28]->init(PointMake(10030, 370), 300, 110);	   // 10030, 370 - 300, 110
	_vCollider.push_back(coll[28]);
	coll[29]->init(PointMake(10630, 0), 450, 380);		   // 10630, 0 - 450, 380
	_vCollider.push_back(coll[29]);
	coll[30]->init(PointMake(10630, 0), 1370, 55);		   // 10630, 0 - 1370, 55
	_vCollider.push_back(coll[30]);
	coll[31]->init(PointMake(10630, 590), 450, 380);	   // 10630, 590 - 450, 380
	_vCollider.push_back(coll[31]);
	coll[32]->init(PointMake(10640, 695), 4000, 150);	   // 10640, 695 - 1370, 150
	_vCollider.push_back(coll[32]);
	coll[33]->init(PointMake(11845, 0), 155, 270);		   // 11845, 0 - 155, 270
	_vCollider.push_back(coll[33]);
	coll[34]->init(PointMake(12000, 0), 100, 480);		   // 12000, 0 - 100, 480
	_vCollider.push_back(coll[34]);

	coll[35]->init(PointMake(12000, 480), 100, 250);	   // 12000, 480 - 100, 115	// 보스방 진입 문
	_vCollider.push_back(coll[35]);

	//coll[36]->init(PointMake(11000, 0), 1600, 50);		   // 11080, 0 - 2300, 150
	//_vCollider.push_back(coll[36]);
	coll[36]->init(PointMake(12100, 0), 1100, 10);		   // 12100, 0 - 1100, 10		// 보스방 천장
	_vCollider.push_back(coll[36]);
	coll[37]->init(PointMake(13100, 0), 110, WINSIZEY);	   // 13100, 0 - 110, WINSIZEY // 보스방 오른쪽 벽
	_vCollider.push_back(coll[37]);


	// 임시 ===================================================================

	//coll[38]->init(PointMake(2373, 685), 63, 200);		   // 2310, 690 - 100, 200
	//_vCollider.push_back(coll[38]);
	//
	//coll[39]->init(PointMake(2437, 680), 64, 100);		   // 3010, 525 - 200, 100
	//_vCollider.push_back(coll[39]);
	//coll[40]->init(PointMake(2500, 675), 63, 200);		   // 2310, 690 - 100, 200
	//_vCollider.push_back(coll[40]);
	//coll[41]->init(PointMake(2564, 670), 64, 100);		   // 3010, 525 - 200, 100
	//_vCollider.push_back(coll[41]);
	//coll[42]->init(PointMake(2628, 665), 63, 200);		   // 2310, 690 - 100, 200
	//_vCollider.push_back(coll[42]);
	//coll[43]->init(PointMake(3010, 560), 64, 100);		   // 3010, 525 - 200, 100
	//_vCollider.push_back(coll[43]);
	//coll[44]->init(PointMake(2310, 690), 63, 200);		   // 2310, 690 - 100, 200
	//_vCollider.push_back(coll[44]);
	//coll[45]->init(PointMake(3010, 525), 64, 100);		   // 3010, 525 - 200, 100
	//_vCollider.push_back(coll[45]);
	//coll[46]->init(PointMake(2310, 690), 63, 200);		   // 2310, 690 - 100, 200
	//_vCollider.push_back(coll[46]);
	//coll[47]->init(PointMake(2310, 690), 64, 100);		   // 3010, 525 - 200, 100
	//_vCollider.push_back(coll[47]);
	//
	//coll[48]->init(PointMake(3946, 540), 64, 200);		   // 2310, 690 - 100, 200
	//_vCollider.push_back(coll[48]);
	
	
	// 0, 680 - 800, 200
	// 800, 630 - 400, 200
	// 1200, 680 - 200, 200
	// 1600, 580 - 400, 200
	// 1600, 210 - 400, 200
	// 2310, 690 - 100, 200
	// 3010, 525 - 200, 100
	// 3510, 370 | 690 - 200
	// 
	// 3920, 210 | 530 - 200
	// 4315, 370 - 200
	// 4515, 575 - 200
	// 5315, 315 - 200
	// 5515, 265 - 200
	// 5625, 700 - 3550
	// 
	// 6015, 160 - 3160
	// 6425, 595 - 140
	// 6975, 540 - 140
	// 7525, 540 - 140
	// 7875, 590 - 140
	// 8775, 540 - 400
	// 6015, 0 - 555, 320
	// 8225, 0 - 155, 325
	// 8775, 0 - 400, 325
	// 9430, 210 - 300, 120
	// 9425, 690 - 300
	// 9625, 210 - 110, 590
	// 10030, 370 - 300, 110
	// 10630, 0 - 450, 380
	// 10630, 0 - 1370, 55
	// 10630, 590 - 450, 380
	// 10640, 695 - 1370, 150
	// 11845, 0 - 155, 270
	// 12000, 0 - 100, 480
	// 12000, 480 - 100, 115	// 보스방 진입 문
	// 11080, 0 - 2300, 150
	// 12100, 0 - 1100, 10		// 보스방 천장
	// 13100, 0 - 110, WINSIZEY // 보스방 오른쪽 벽

}

void objectManager::removeCollider()
{
}
