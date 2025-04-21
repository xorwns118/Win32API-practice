#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // 프로그램 종료시 DC 메모리 해제

	DeleteDC(m_memDC); // ID를 받아와 썼기 때문에 해제 요청
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // 리턴값이 레지스터에 임시적으로 저장된 후 반환해주기 때문에 사이즈가 크면 성능 저하를 초래함 
												// => 주소를 받아 직접 주는 방식으로 해결함
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	m_hDC = GetDC(m_hWnd); // 내부적으로 DC 가 생기면서 활용 가능, 메세지와 엮이면서 돌아가는 것이 아니라 해제 필요없이 프로그램 종료시 지우면 됨

	// 이중 버퍼링 용도의 비트맵과 DC 를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // 깉은 해상도의 비트맵을 생성함
	m_memDC = CreateCompatibleDC(m_hDC); // 위와 동일하게 같은 DC 생성

	// BitMap : 해상도 영역만큼의 픽셀 데이터 묶음
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // 이전에 쓰던 비트맵을 선택해줌
	DeleteObject(hOldBit); // 반환된 이전의 비트맵을 삭제

	// 자주 사용할 펜 및 브러쉬 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

// Window의 메세지 구조를 알기까지 C 언어 이해도가 필요, 이후 게임을 만드는 부분부터는 C++ 사용


void CCore::progress()
{
	/*static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount();
	int iCurCont = GetTickCount();
	if (GetTickCount() - iPrevCount > 1000)
	{
		iPrevCount = iCurCont;
		callCount = 0;
	}*/

	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	CSceneMgr::GetInst()->update();
	CCollisionMgr::GetInst()->update();

	// =========
	// Rendering
	// =========
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC); // 그려질 목적지를 알기 위해 memDC 를 인자로 받음

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// 이 부분에서 Frame drop이 꽤 크게 일어났지만 고정비용이기 때문에
	// 나머지 작업에서 갑자기 크게 떨어질 일은 없음 => 복사해서 그리는 작업은 항상 일치함.
	// Debug Mode 에서는 표준라이브러리에 예외처리가 상당히 많이 들어가있기 때문에 Frame Drop률이 큼
	// 게임을 만들고 빌드할 땐 Realese 버전으로

	// CPU 가 이 수많은 반복문을 처리하기엔 너무 빡세기 때문에 등장한 장치가 GPU
	// WinApi 에선 CPU 만을 이용한 수업, GPU는 DirecX 사용부터
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
