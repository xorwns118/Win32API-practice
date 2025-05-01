#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_tInfo{}
	, m_pAI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::update()
{
	m_pAI->update();
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{

	}
}

// FSM (Finit State Machine) 유한 상태 기계
// 여러가지 상태를 두고 전환되는 패턴
// 학습하는 인공지능 패턴이 아닌, 노가다로 만드는 패턴

// 팩토리 패턴 (Factory Pattern)
// 정형화된 패턴들을 매번 코드로 나열하는 것이 아닌
// 자주사용하는 로직을 함수화시켜서 모아두는 패턴
// 공장에서 물건을 찍어내듯