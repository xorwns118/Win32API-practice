#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CMonFactory.h"
 
CScene_Start::CScene_Start()
{

}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pObj->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// Monster 배치
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(vResolution / 2.f - Vec2(0.f, 300.f)));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	//int iMonCount = 1;
	//float fMoveDist = 25.f;
	//float fObjScale = 50.f;

	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	//
	//AI* pAI = new AI;
	//pAI->AddState(new CIdleState);
	//pAI->AddState(new CTraceState);

	//CMonster* pMonsterObj = nullptr;
	//
	//for (int i = 0; i < iMonCount; ++i)
	//{
	//	// Monster Object 추가
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	pMonsterObj->SetPos(vResolution / 2.f - Vec2(0.f, 300.f));
	//	pMonsterObj->SetAI(pAI);

	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}

	// 타일 로딩
	//LoadTile(L"Tile\\Start.tile");

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera Effect 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}