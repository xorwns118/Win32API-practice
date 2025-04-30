#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(CScene::*SCENE_MEMFUNC)(void); // CScene 에 구현 되어있는(자식 클래스 포함) 멤버 함수를 호출하는 함수 포인터
// => 최상위 클래스를 만들어 모두 묶으면 최상위 부모클래스를 지정하여 자식 객체의 함수를 함수 포인터로 호출할 수 있음
// 멤버함수 선언 시 정확한 클래스 정보를 알아야하기 때문에 전방선언으로 넘어가지 않음
// 클래스의 멤버함수로 받겠다고 했는데,  클래스에 대한 정보가 없기 때문에 바인딩할 때 문제가 생김
// 넘어온 주소값들은 정확하지만, 어떤 객체이고 어떤 클래스타입의 멤버함수인지 모르는 상태에서 호출하기 때문
typedef void(CObject::*Object_MEMFUNC)(void);

class CBtnUI : public CUI
{
private:
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;

	SCENE_MEMFUNC	m_pSceneFunc;
	CScene*			m_pSceneInst;

public:
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{ 
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);
	
	CLONE(CBtnUI);

public:
	CBtnUI();
	~CBtnUI();
};

