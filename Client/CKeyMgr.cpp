#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,

	//LAST
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHWnd();
	HWND hWnd = GetFocus(); // 현재 포커싱 되어있는 윈도우 핸들 값, 없으면 0(nullptr)

	// 윈도우 포커싱 중일 떄 키 이벤트 동작
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있었다.
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에는 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			// 키가 안눌려있었다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// Mouse 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(CCore::GetInst()->GetMainHWnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}
	// 윈도우 포커싱 해제 상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if(m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}