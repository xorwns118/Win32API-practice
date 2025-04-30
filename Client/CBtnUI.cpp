#include "global.h"
#include "CBtnUI.h"

#include "CScene.h"
#include "CScene_Tool.h"

CBtnUI::CBtnUI()
	: CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneFunc(nullptr)
	, m_pSceneInst(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	if (m_pFunc != nullptr)
	{
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneFunc && m_pSceneInst)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}

// UI에 이미지 삽입 해서 원하는 타일 모아놓고 페이징 기능 구현 하고, 타일 배치 기능 넣기