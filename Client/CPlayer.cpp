#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture 로딩하기
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width(); // 화면 밖으로 나가는경우가 음수일 수 있기 때문에 unsigned int 를 int 로 캐스팅
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight, m_pTex->GetDC()
		, 0, 0, SRCCOPY);*/

	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight, RGB(255, 0, 255)); 

	// TransparentBlt 함수 자체가 복사한다는 개념이기 때문에 SRCCOPY 와 같은 인자를 필요로 하지 않음.
	// 대신 무시할 색상 RGB 매크로 입력
	// Windows.h 가 wingdi.h 를 참조하고 있어 사용할 수 있지만 현재 사용된 부분에서 실제 구현된 부분이 없기 때문에 LNK 오류 뜸
	// => pch 파일에 라이브러리 참조 선언 (#pragma commet(lib, "name"))

	// 마젠타 색상
	// 255, 0, 255 로 이루어진 색상, 주로 빈공간에 채워넣고 무시되는 용도로 사용하고,
	// 거의 안쓰이는 색상이기에 빈공간을 채울 때 주로 사용
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}