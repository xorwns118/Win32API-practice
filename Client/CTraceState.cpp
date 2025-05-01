#include "global.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	// Å¸°ÙÆÃ µÈ Player ¸¦ ÂÑ¾Æ°£´Ù.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);

	Vec2 vDiff = vPlayerPos - vMonPos;

	if (vDiff.Length() < GetMonster()->GetInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), MON_STATE::IDLE);
	}
} // AStar?

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
