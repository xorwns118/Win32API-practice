#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "SelectGDI.h"

#include "resource.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_pMemTex(nullptr)
	, m_arrBrush{}
	, m_arrPen{}
	, m_hMenu(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // ���α׷� ����� DC �޸� ����

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);
	
	// �޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd); // ���������� DC �� ����鼭 Ȱ�� ����, �޼����� ���̸鼭 ���ư��� ���� �ƴ϶� ���� �ʿ���� ���α׷� ����� ����� ��

	// CTexture ���� Create �Լ��� ����� ��// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �� �����.
	//m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // ���� �ػ��� ��Ʈ���� ������
	//m_memDC = CreateCompatibleDC(m_hDC); // ���� �����ϰ� ���� DC ����
	// BitMap : �ػ� ������ŭ�� �ȼ� ������ ����
	//HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // ������ ���� ��Ʈ���� ��������
	//DeleteObject(hOldBit); // ��ȯ�� ������ ��Ʈ���� ����


	// ���� ���۸� �뵵�� �ؽ��� ������ �����.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// ���� ����� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

// Window�� �޼��� ������ �˱���� C ��� ���ص��� �ʿ�, ���� ������ ����� �κк��ʹ� C++ ���


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

	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
	// ============
	CSceneMgr::GetInst()->update();
	
	// �浹 üũ
	CCollisionMgr::GetInst()->update();

	// UI �̺�Ʈ üũ
	CUIMgr::GetInst()->update();

	// =========
	// Rendering
	// =========
	// ȭ�� Clear
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC()); // �׷��� �������� �˱� ���� memDC �� ���ڷ� ����
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// �� �κп��� Frame drop�� �� ũ�� �Ͼ���� ��������̱� ������
	// ������ �۾����� ���ڱ� ũ�� ������ ���� ���� => �����ؼ� �׸��� �۾��� �׻� ��ġ��.
	// Debug Mode ������ ǥ�ض��̺귯���� ����ó���� ����� ���� ���ֱ� ������ Frame Drop���� ŭ
	// ������ ����� ������ �� Realese ��������

	// CPU �� �� ������ �ݺ����� ó���ϱ⿣ �ʹ� ������ ������ ������ ��ġ�� GPU
	// WinApi ���� CPU ���� �̿��� ����, GPU�� DirecX ������

	// ==============
	// �̺�Ʈ ����ó��
	// ==============
	CEventMgr::GetInst()->update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// red blue green pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr); // HMENU ���ڿ� nullptr �� �־� �޴��ٸ� ����.
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (long)_vResolution.x, (long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // ���ϰ��� �������Ϳ� �ӽ������� ����� �� ��ȯ���ֱ� ������ ����� ũ�� ���� ���ϸ� �ʷ��� 
	// => �ּҸ� �޾� ���� �ִ� ������� �ذ���
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}
