#pragma once
#include "CScene.h"

class CScene_Tool : public CScene
{
private:
	CUI* m_pUI;

public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();

public:
	CScene_Tool();
	~CScene_Tool();
};

