// main 강의 정리

//#include "framework.h"
//#include "Client.h"
#include "pch.h"
//#include "CCore.h"

// 전역 변수:
//HINSTANCE hInst;                                // 현재 인스턴스입니다.
//HWND      g_hwnd;                               // 메인 윈도우
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 지역
// 전역
// 정적 (데이터 영역)
// 1. 함수 안에
// 2. 파일
// 3. 클래스 안에
// 외부
//class CClass
//{
//private:
//    int m_i;
//
//    static int m_iStatic; // 정적 멤버 (데이터 영역)
//
//public:
//    void func()
//    {
//        m_i = 0;
//        m_iStatic = 0;
//    }
//
//    // 정적 멤버함수, 객체없이 호출 가능, this 가 없다(멤버 접근 불가), 정적 멤버는 접근 가능
//    static void Func()
//    {
//        // this로 private한 멤버 변수 호출 불가능하기 때문에 정적 멤버함수를 호출 할 수 있는것
//        m_iStatic = 0; // this 키워드 사용 불가
//    }
//};

//int CClass::m_iStatic = 0; // 데이터 초기에 올라가야하는 값을 반드시 초기화해야함. 안하면 링크오류
//
//// SAL 주석 _In_ : 데이터가 함수에 입력된다. _In_opt_ : 부가적인 데이터 (optional)
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, /*실행 된 프로세스의 시작 주소(가상 메모리의 주소, 물리적인 주소는 다름)*/
//    _In_opt_ HINSTANCE hPrevInstance, /*이전 프로세스 시작 주소 (초창기 윈도우 방식, 지금은 사용되지 않음)*/
//    _In_ LPWSTR lpCmdLine, /*CMD 명령어로 기본 프로그램 시작할 때 옵션 인자 값, 게임을 다루면서 쓰지 않을 예정*/
//    _In_ int nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance); // 딱히 의미 없다는 것을 알려줌 (쓰이지 않는다.)
//    UNREFERENCED_PARAMETER(lpCmdLine); // 컴파일러가 알아서 무시함.
//
//    // TODO: 여기에 코드를 입력합니다.
//    //CCore* pCore = CCore::GetInstance();
//
//    // 전역 문자열을 초기화합니다.
//    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    //LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
//
//    // 윈도우 정보 등록
//    MyRegisterClass(hInstance);
//
//    // 윈도우 생성
//    if (!InitInstance(hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    // Core 초기화
//    if (FAILED(CCore::GetInst()->init(g_hwnd, POINT{ 1280, 768 })))
//    {
//        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
//
//        return FALSE;
//    }
//
//    // 단축키 테이블 정보 로딩
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
//
//    MSG msg;
//
//    // 윈도우 메세지 이벤트가 없을 경우를 대비할 이벤트를 강제로 일으키는 타이머, Kernel Obj
//    //SetTimer(g_hwnd, 10, 0, nullptr);
//
//    // 기본 메시지 루프입니다:
//    // msg 구조체에 값을 채워넣기 위해 주소값을 받아옴
//
//    // GetMessage
//    // 메세지 큐에서 메세지를 확인될 때 까지 대기
//    // msg.message == WM_QUIT 인 경우 false 를 반환 -> 프로그램 종료
//
//    // PeekMessage
//    // 메세지 유무와 관계없이 반환
//    // 메세지큐에서 메세지를 확인한 경우 true, 메세지가 없는 경우 false를 반환한다.
//    // Peek 몰래 보다. => 메세지를 살짝 보겠다. => 메세지가 확인될 때 까지 대기 할 필요가 없음.
//
//    while (true) // 기본으로 제공되는 GetMessage 를 이용해 게임을 만들 수 있으나 비효율적임, 적합한 형태로 바꿈
//    {
//        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//        {
//            if (msg.message == WM_QUIT)
//                break;
//
//            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//            {
//                TranslateMessage(&msg);
//                DispatchMessage(&msg);
//            }
//        }
//        // 메세지가 발생하지 않는 대부분의 시간
//        else
//        {
//            // Game code 수행
//            // 디자인 패턴(설계 유형)
//            // 상황마다 다르고 언어마다 특성을 살려 표현하기 때문에, 알아두면 좋으나 많은 비중을 차지하진 않음.
//            // ********싱글톤 패턴은 중요********
//
//            CCore::GetInst()->progress();
//        }
//    }
//
//    // kernel obj 삭제
//    //KillTimer(g_hwnd, 10);
//
//    return (int)msg.wParam;
//}
//
//
//
////
////  함수: MyRegisterClass()
////
////  용도: 창 클래스를 등록합니다.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc = WndProc;
//    wcex.cbClsExtra = 0;
//    wcex.cbWndExtra = 0;
//    wcex.hInstance = hInstance;
//    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
//    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CLIENT); // 메뉴바
//    //wcex.lpszClassName = szWindowClass;
//    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   함수: InitInstance(HINSTANCE, int)
////
////   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
////
////   주석:
////
////        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
////        주 프로그램 창을 만든 다음 표시합니다.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
//
//   // g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//        //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//    if (!g_hwnd)
//    {
//        return FALSE;
//    }
//
//    ShowWindow(g_hwnd, nCmdShow);
//    UpdateWindow(g_hwnd);
//
//    return TRUE;
//}
//
////
////  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  용도: 주 창의 메시지를 처리합니다.
////
////  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
////  WM_PAINT    - 주 창을 그립니다.
////  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//#include <vector>
//
//using std::vector;
//
//struct tObjInfo
//{
//    POINT g_ptObjPos;
//    POINT g_ptObjScale;
//};
//
//vector<tObjInfo> g_vecInfo;
//
//// 좌 상단
//POINT g_ptLT;
//// 우 하단
//POINT g_ptRB;
//
//bool bLBtnDown = false;
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//    {
//        int wmId = LOWORD(wParam);
//        // 메뉴 선택을 구문 분석합니다:
//        switch (wmId)
//        {
//        case IDM_ABOUT:
//            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//            break;
//        case IDM_EXIT:
//            DestroyWindow(hWnd);
//            break;
//        default:
//            return DefWindowProc(hWnd, message, wParam, lParam);
//        }
//    }
//    break;
//    case WM_PAINT: // 무효화 영역(Invalidate)이 발생한 경우
//    {
//        PAINTSTRUCT ps;
//        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
//
//        // 윈도우 핸들 : 커널 오브젝트를 다룰 수 있는 ID(핸들) 값
//        // 윈도우 좌표
//        // HDC ?
//
//        // Device Context 만들어서 ID 를 반환
//        HDC hdc = BeginPaint(hWnd, &ps); // Device Context (그리기) 그리기 작업 수행, 필요한 Data 집합
//        // DC 의 목적지는 hWnd
//        // DC 의 펜은 기본펜(Black)
//        // DC 의 브러쉬는 기본 브러쉬(White)
//
//        // 직접 펜을 만들어서 DC 에 지급
//        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));//GetStockObject(); 미리 만들어놓은 자주쓰는 오브젝트를 가져옴
//
//        // 타입에 따라 바뀌어야 하기 때문에 반환타입을 특정 포인터가 아닌 void 포인터 방식을 사용, 강제 캐스팅이 필요함
//        HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); // 기본 Pen ID 값을 받아둠
//        HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush); // 기본 Brush ID 값을 받아둠
//
//        // 변경된 펜으로 사각형 그림
//        if (bLBtnDown)
//            Rectangle(hdc, g_ptLT.x, g_ptLT.y, g_ptRB.x, g_ptRB.y); // pixel 단위
//
//        // 추가된 사각형들도 그려준다.
//        for (size_t i = 0; i < g_vecInfo.size(); ++i)
//        {
//            Rectangle(hdc
//                , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
//                , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
//                , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
//                , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
//        }
//
//        // DC의 펜과 브러쉬를 원래의 것으로 되돌림
//        SelectObject(hdc, hDefaultPen);
//        SelectObject(hdc, hDefaultBrush);
//
//        // 다 쓴 펜, 브러쉬 삭제 요청
//        DeleteObject(hRedPen);
//        DeleteObject(hDefaultBrush);
//
//        // 그리기 종료
//        EndPaint(hWnd, &ps);
//    }
//    break;
//    case WM_KEYDOWN:
//    {
//        switch (wParam)
//        {
//        case VK_UP:
//            //g_ptObjPos.y -= 10;
//            InvalidateRect(hWnd, nullptr, true);
//
//            break;
//
//        case VK_DOWN:
//            //g_ptObjPos.y += 10;
//            InvalidateRect(hWnd, nullptr, true);
//
//            break;
//
//        case VK_LEFT:
//            //g_ptObjPos.x -= 10;
//            InvalidateRect(hWnd, nullptr, true);
//
//            break;
//
//        case VK_RIGHT:
//            //g_ptObjPos.x += 10;
//            InvalidateRect(hWnd, nullptr, true);
//
//            break;
//        }
//    }
//    break;
//
//    case WM_LBUTTONDOWN:
//        g_ptLT.x = LOWORD(lParam); // 마우스 x 좌표
//        g_ptLT.y = HIWORD(lParam); // 마우스 y 좌표
//        bLBtnDown = true;
//        break;
//
//    case WM_MOUSEMOVE:
//        g_ptRB.x = LOWORD(lParam);
//        g_ptRB.y = HIWORD(lParam);
//        //InvalidateRect(hWnd, nullptr, true);
//        break;
//
//    case WM_LBUTTONUP:
//    {
//        tObjInfo info = {};
//        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
//        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;
//
//        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
//        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);
//
//        g_vecInfo.push_back(info);
//        bLBtnDown = false;
//        InvalidateRect(hWnd, nullptr, true);
//    }
//    break;
//
//    case WM_TIMER:
//        break;
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
//