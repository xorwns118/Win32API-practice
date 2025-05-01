// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

// 각 파일에서 다른 헤더를 참조에 각각의 cpp 파일을 받아오기 때문에 빌드 속도가 줄어듦 => Unity Build로 해결 (게임엔진 말하는거 아님)
// Unity Build : main.cpp 에 모든 파일을 때려박아 한번에 빌드 => 빌드 속도가 올라감.
// Visual Studio 에서 제공되지만 실험단계, 숨겨놨음.
// 아무 PropertyGroup 사이에
// <PropertyGroup>
//   <EnableUnitySupport>true</EnableUnitySupport>
// </PropertyGroup>
// 삽입 후 속성 -> UnityBuild -> 최소 소스 수 10개(메모리가 작성할 수 있는 최대 범위가 있기 때문에 코드량 상황에 맞게) 설정
// Unity 파일 디렉토리 $(ProjectDir)\Unity\ 설정
// 일반 -> 다중 프로세서 컴파일 (예) 설정
// 미리 컴파일된 헤더와 충돌이 일어날 수 있기 때문에, 사용하지 않음으로 설정.


#include "framework.h"
#include "Client.h"
#include "global.h"
#include "CCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE   hInst;                              // 현재 인스턴스입니다.
HWND        g_hwnd;                             // 메인 윈도우
WCHAR       szTitle[MAX_LOADSTRING];            // 제목 표시줄 텍스트입니다.
WCHAR       szWindowClass[MAX_LOADSTRING];      // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL 주석 _In_ : 데이터가 함수에 입력된다. _In_opt_ : 부가적인 데이터 (optional)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, /*실행 된 프로세스의 시작 주소(가상 메모리의 주소, 물리적인 주소는 다름)*/
                     _In_opt_ HINSTANCE hPrevInstance, /*이전 프로세스 시작 주소 (초창기 윈도우 방식, 지금은 사용되지 않음)*/
                     _In_ LPWSTR lpCmdLine, /*CMD 명령어로 기본 프로그램 시작할 때 옵션 인자 값, 게임을 다루면서 쓰지 않을 예정*/
                     _In_ int nCmdShow)
{
    // 메모리 릭(누수) 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(376); // 쓰고나면 꼭 지우던 주석처리하던 하자

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    //CCore* pCore = CCore::GetInstance();

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화
    if (FAILED(CCore::GetInst()->init(g_hwnd, POINT{1280, 768})))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

        return FALSE;
    }
    
    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    // msg 구조체에 값을 채워넣기 위해 주소값을 받아옴

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        // 메세지가 발생하지 않는 대부분의 시간
        else
        {
            CCore::GetInst()->progress();
        }
    }

    // kernel obj 삭제
    //KillTimer(g_hwnd, 10);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; // MAKEINTRESOURCEW(IDC_CLIENT); // 메뉴바
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hwnd)
   {
      return FALSE;
   }

   ShowWindow(g_hwnd, nCmdShow);
   UpdateWindow(g_hwnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); // 모달 방식, 본인이 해당 윈도우의 포커싱을 가져감
                break;
            case ID_MENU_TILE:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TILE_COUNT), hWnd, TileCountProc);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역(Invalidate)이 발생한 경우
        {
            PAINTSTRUCT ps;
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // Device Context 만들어서 ID 를 반환
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context (그리기) 그리기 작업 수행, 필요한 Data 집합
            // 메세지를 처리하는 부분의 전용 함수

            //Rectangle(hdc, 1180, 668, 1280, 768); // pixel 단위

            // 해제하지 않으면 해제하라는 메세지가 무한히 쌓임
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    
        break;
        
    case WM_LBUTTONDOWN:
        
        break;

    case WM_MOUSEMOVE:
        
        break;

    case WM_LBUTTONUP:
    
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// 1. 플레이어 미사일 종류 추가
// 2. 몬스터 미사일 패턴 추가