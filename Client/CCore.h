#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능
//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	 정적 멤버 함수
//	static CCore* GetInstance()
//	{
//		 최초 호출 된 경우
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//
//		 메모리 영역에 이미 있다면, nullptr 반환
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
	SINGLE(CCore); // 동적할당 방식이 아니기 때문에 해제를 신경쓰지 않아도 된다. => 지울 수 없다.

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hDC;			// 메인 윈도우에 Draw 할 DC

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