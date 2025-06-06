#include "global.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"

CPlayer::CPlayer()
	: m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::IDLE)
	, m_iDir(1)
	, m_iPrevDir(-1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.bmp");
	
	CreateAnimator();

	//GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0.f, 65.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.6f, 3);
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 195.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.6f, 3);

	//GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	//// Animation 저장해보기
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");

	CreateGravity();

	GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	update_state();

	update_move();

	update_animation();
		
	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	//int iWidth = (int)m_pTex->Width(); // 화면 밖으로 나가는경우가 음수일 수 있기 때문에 unsigned int 를 int 로 캐스팅
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();

	// BitBlt(_dc
	// 		, int(vPos.x - (float)(iWidth / 2))
	// 		, int(vPos.y - (float)(iHeight / 2))
	// 		, iWidth, iHeight, m_pTex->GetDC()
	// 		, 0, 0, SRCCOPY);
	// 
	// TransparentBlt(_dc
	// 		, int(vPos.x - (float)(iWidth / 2))
	// 		, int(vPos.y - (float)(iHeight / 2))
	// 		, iWidth, iHeight, m_pTex->GetDC()
	// 		, 0, 0, iWidth, iHeight, RGB(255, 0, 255)); 

	// TransparentBlt 함수 자체가 복사한다는 개념이기 때문에 SRCCOPY 와 같은 인자를 필요로 하지 않음.
	// 대신 무시할 색상 RGB 매크로 입력
	// Windows.h 가 wingdi.h 를 참조하고 있어 사용할 수 있지만 현재 사용된 부분에서 실제 구현된 부분이 없기 때문에 LNK 오류 뜸
	// => pch 파일에 라이브러리 참조 선언 (#pragma commet(lib, "name"))

	// 마젠타 색상
	// 255, 0, 255 로 이루어진 색상, 주로 빈공간에 채워넣고 무시되는 용도로 사용하고,
	// 거의 안쓰이는 색상이기에 빈공간을 채울 때 주로 사용

	// 컴포넌트(충돌체, etc...) 가 있는 경우 렌더
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::JUMP)
		{
			m_eCurState = PLAYER_STATE::WALK;
		}
	}

	if (GetRigidBody()->GetSpeed() == 0.f && m_eCurState != PLAYER_STATE::JUMP)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	else
	{
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;

		if (GetRigidBody())
		{
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -400.f));
		}
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	Vec2 vForce(0.f, 0.f);

	if (KEY_HOLD(KEY::A))
	{
		vForce.x -= 200.f;
	}

	if (KEY_HOLD(KEY::D))
	{
		vForce.x += 200.f;
	}

	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}

	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}

	// 대각선 이동 시 힘 정규화
	if (vForce.x != 0.f && vForce.y != 0.f)
	{
		vForce.Normalize();
		vForce *= 200.f;
	}

	pRigid->AddForce(vForce);
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_iDir == m_iPrevDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
		if (m_iDir == 1)
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		else
			GetAnimator()->Play(L"IDLE_LEFT", true);
		break;
	case PLAYER_STATE::WALK:
		if (m_iDir == 1)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else
			GetAnimator()->Play(L"WALK_LEFT", true);
		break;
	case PLAYER_STATE::JUMP:
		break;
	case PLAYER_STATE::ATTACK:
		break;
	case PLAYER_STATE::DEAD:
		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOther = _pOther->GetObj();

	if (pOther->GetName() == L"Ground")
	{
		Vec2 vPos = GetPos();
		if (vPos.y < pOther->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}
