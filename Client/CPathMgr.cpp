#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::init()
{
	// F5 를 눌러 실행하거나 Ctrl + F5 를 눌러 실행하게 되면 지정해놓은 Output 파일 내의 bin 폴더의 자체적인 프로그램이 아닌
	// Visual Studio 라는 개발 툴을 이용해 실행하게 되기 때문에 프로젝트의 파일이 모여있는 경로를 포커싱함.
	// => 프로젝트 속성 -> 구성 속성 -> 디버깅 -> 작업 디렉토리를 $(SolutionDir)\Output\bin\ 으로 지정 (출력파일을 지정해둔 폴더로 접근)
	GetCurrentDirectory(255, m_szContentPath);
	int iLen = (int)wcslen(m_szContentPath);

	// 상위 폴더로 (라이브러리 존재) 경로를 끊고 싶은 부분에 null 에 대응되는 \0 삽입
	for (int i = iLen - 1; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(CCore::GetInst()->GetMainHWnd(), m_szContentPath);
}

