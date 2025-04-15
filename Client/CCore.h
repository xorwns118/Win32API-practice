#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	 ���� ��� �Լ�
//	static CCore* GetInstance()
//	{
//		 ���� ȣ�� �� ���
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//
//		 �޸� ������ �̹� �ִٸ�, nullptr ��ȯ
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (g_pInst != nullptr)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore()
//	{}
//	~CCore()
//	{}
//};

class CCore
{
	SINGLE(CCore); // �����Ҵ� ����� �ƴϱ� ������ ������ �Ű澲�� �ʾƵ� �ȴ�. => ���� �� ����.

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hDC;			// ���� �����쿡 Draw �� DC

	HBITMAP	m_hBit;
	HDC		m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHWnd() { return m_hWnd; }
};