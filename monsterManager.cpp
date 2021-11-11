#include "stdafx.h"
#include "MonsterManager.h"

HRESULT MonsterManager::init()
{
	return S_OK;
}

void MonsterManager::release()
{

}

void MonsterManager::update()
{

	for (_viNormalTree = _vNormalTree.begin(); _viNormalTree != _vNormalTree.end(); ++_viNormalTree)
	{
		(*_viNormalTree)->update();
	}
}

void MonsterManager::render()
{
	for (_viNormalTree = _vNormalTree.begin(); _viNormalTree != _vNormalTree.end(); ++_viNormalTree)
	{
		(*_viNormalTree)->render();
	}
}

void MonsterManager::SetMonster(int stageNum)
{
	if (stageNum == 3)
	{
		monster* _NormalTree1;
		_NormalTree1 = new NormalTree;
		_NormalTree1->init("NormalTree_IDLE", PointMake(792, 1590));

		_vNormalTree.push_back(_NormalTree1);

		monster* _NormalTree2;
		_NormalTree2 = new NormalTree;
		_NormalTree2->init("NormalTree_IDLE", PointMake(1050, 1300));

		_vNormalTree.push_back(_NormalTree2);

		monster* _NormalTree3;
		_NormalTree3 = new NormalTree;
		_NormalTree3->init("NormalTree_IDLE", PointMake(1500, 980));

		_vNormalTree.push_back(_NormalTree3);

		monster* _NormalTree4;
		_NormalTree4 = new NormalTree;
		_NormalTree4->init("NormalTree_IDLE", PointMake(2160, 1590));

		_vNormalTree.push_back(_NormalTree4);

		monster* _NormalTree5;
		_NormalTree5 = new NormalTree;
		_NormalTree5->init("NormalTree_IDLE", PointMake(2100, 1300));

		_vNormalTree.push_back(_NormalTree5);

		monster* _NormalTree6;
		_NormalTree6 = new NormalTree;
		_NormalTree6->init("NormalTree_IDLE", PointMake(2600, 900));

		_vNormalTree.push_back(_NormalTree6);
	}

	if (stageNum == 4)
	{
		monster* _NormalTree1;
		_NormalTree1 = new NormalTree;
		_NormalTree1->init("NormalTree_IDLE", PointMake(792, 1690));

		_vNormalTree.push_back(_NormalTree1);

		monster* _NormalTree2;
		_NormalTree2 = new NormalTree;
		_NormalTree2->init("NormalTree_IDLE", PointMake(1050, 1300));

		_vNormalTree.push_back(_NormalTree2);

		monster* _NormalTree3;
		_NormalTree3 = new NormalTree;
		_NormalTree3->init("NormalTree_IDLE", PointMake(1200, 1165));

		_vNormalTree.push_back(_NormalTree3);

		monster* _NormalTree4;
		_NormalTree4 = new NormalTree;
		_NormalTree4->init("NormalTree_IDLE", PointMake(1500, 980));

		_vNormalTree.push_back(_NormalTree4);

		monster* _NormalTree5;
		_NormalTree5 = new NormalTree;
		_NormalTree5->init("NormalTree_IDLE", PointMake(1300, 500));

		_vNormalTree.push_back(_NormalTree5);

		monster* _NormalTree6;
		_NormalTree6 = new NormalTree;
		_NormalTree6->init("NormalTree_IDLE", PointMake(1700, 1360));

		_vNormalTree.push_back(_NormalTree6);
	}

	if (stageNum == 5)
	{
		monster* _NormalTree1;
		_NormalTree1 = new NormalTree;
		_NormalTree1->init("NormalTree_IDLE", PointMake(800, 1600));

		_vNormalTree.push_back(_NormalTree1);

		monster* _NormalTree2;
		_NormalTree2 = new NormalTree;
		_NormalTree2->init("NormalTree_IDLE", PointMake(1600, 1800));

		_vNormalTree.push_back(_NormalTree2);

		monster* _NormalTree3;
		_NormalTree3 = new NormalTree;
		_NormalTree3->init("NormalTree_IDLE", PointMake(800, 2200));

		_vNormalTree.push_back(_NormalTree3);

		monster* _NormalTree4;
		_NormalTree4 = new NormalTree;
		_NormalTree4->init("NormalTree_IDLE", PointMake(1600, 2000));

		_vNormalTree.push_back(_NormalTree4);

		monster* _NormalTree5;
		_NormalTree5 = new NormalTree;
		_NormalTree5->init("NormalTree_IDLE", PointMake(800, 1500));

		_vNormalTree.push_back(_NormalTree5);

		monster* _NormalTree6;
		_NormalTree6 = new NormalTree;
		_NormalTree6->init("NormalTree_IDLE", PointMake(1600, 1500));

		_vNormalTree.push_back(_NormalTree6);

		monster* _NormalTree7;
		_NormalTree7 = new NormalTree;
		_NormalTree7->init("NormalTree_IDLE", PointMake(1000, 1500));

		_vNormalTree.push_back(_NormalTree7);

		monster* _NormalTree8;
		_NormalTree8 = new NormalTree;
		_NormalTree8->init("NormalTree_IDLE", PointMake(1400, 1500));

		_vNormalTree.push_back(_NormalTree8);

		monster* _NormalTree9;
		_NormalTree9 = new NormalTree;
		_NormalTree9->init("NormalTree_IDLE", PointMake(1200, 1500));

		_vNormalTree.push_back(_NormalTree9);

		monster* _NormalTree10;
		_NormalTree10 = new NormalTree;
		_NormalTree10->init("NormalTree_IDLE", PointMake(2300, 1600));

		_vNormalTree.push_back(_NormalTree10);
	}

}

void MonsterManager::monsterMove()
{
	for (_viNormalTree = _vNormalTree.begin(); _viNormalTree != _vNormalTree.end(); ++_viNormalTree)
	{
		(*_viNormalTree)->render();
	}

}
