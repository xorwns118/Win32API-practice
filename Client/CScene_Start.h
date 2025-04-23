#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
public:
	// 오버라이딩 했기 때문에 virtual 선언 필요 없지만, 
	// 추상클래스이기 때문에 모르고 넘길 수 있기에 명시해주는 것이 좋음
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

