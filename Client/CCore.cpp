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
	ReleaseDC(m_hWnd, m_hDC); // ���α׷� ����� DC �޸� ����

	DeleteDC(m_memDC); // ID�� �޾ƿ� ��� ������ ���� ��û
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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // ���ϰ��� �������Ϳ� �ӽ������� ����� �� ��ȯ���ֱ� ������ ����� ũ�� ���� ���ϸ� �ʷ��� 
												// => �ּҸ� �޾� ���� �ִ� ������� �ذ���
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	m_hDC = GetDC(m_hWnd); // ���������� DC �� ����鼭 Ȱ�� ����, �޼����� ���̸鼭 ���ư��� ���� �ƴ϶� ���� �ʿ���� ���α׷� ����� ����� ��

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // ���� �ػ��� ��Ʈ���� ������
	m_memDC = CreateCompatibleDC(m_hDC); // ���� �����ϰ� ���� DC ����

	// BitMap : �ػ� ������ŭ�� �ȼ� ������ ����
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // ������ ���� ��Ʈ���� ��������
	DeleteObject(hOldBit); // ��ȯ�� ������ ��Ʈ���� ����

	// ���� ����� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
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

	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	CSceneMgr::GetInst()->update();
	CCollisionMgr::GetInst()->update();

	// =========
	// Rendering
	// =========
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC); // �׷��� �������� �˱� ���� memDC �� ���ڷ� ����

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// �� �κп��� Frame drop�� �� ũ�� �Ͼ���� ��������̱� ������
	// ������ �۾����� ���ڱ� ũ�� ������ ���� ���� => �����ؼ� �׸��� �۾��� �׻� ��ġ��.
	// Debug Mode ������ ǥ�ض��̺귯���� ����ó���� ����� ���� ���ֱ� ������ Frame Drop���� ŭ
	// ������ ����� ������ �� Realese ��������

	// CPU �� �� ������ �ݺ����� ó���ϱ⿣ �ʹ� ������ ������ ������ ��ġ�� GPU
	// WinApi ���� CPU ���� �̿��� ����, GPU�� DirecX ������
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
