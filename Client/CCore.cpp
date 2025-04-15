#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"

//CCore* CCore::g_pInst = nullptr;

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // ���α׷� ����� DC �޸� ����

	DeleteDC(m_memDC); // ID�� �޾ƿ� ��� ������ ���� ��û
	DeleteObject(m_hBit);
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

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2( float(m_ptResolution.x / 2), float(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2( 100, 100 ));

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

	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 0x8000, ���ϰ����� ���� ��Ʈ�� on �Ǿ������� true
	{
		vPos.x -= 200.f * fDT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * fDT;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// ȭ�� clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// �׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC, int(vPos.x - vScale.x / 2.f)
				   , int(vPos.y - vScale.y / 2.f)
				   , int(vPos.x + vScale.x / 2.f)
				   , int(vPos.y + vScale.y / 2.f));

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		 , m_memDC, 0, 0, SRCCOPY);

	// �� �κп��� Frame drop�� �� ũ�� �Ͼ���� ��������̱� ������
	// ������ �۾����� ���ڱ� ũ�� ������ ���� ���� => �����ؼ� �׸��� �۾��� �׻� ��ġ��.
	// Debug Mode ������ ǥ�ض��̺귯���� ����ó���� ����� ���� ���ֱ� ������ Frame Drop���� ŭ
	// ������ ����� ������ �� Realese ��������
	
	// CPU �� �� ������ �ݺ����� ó���ϱ⿣ �ʹ� ������ ������ ������ ��ġ�� GPU
	// WinApi ���� CPU ���� �̿��� ����, GPU�� DirecX ������
}
