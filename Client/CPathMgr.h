#pragma once

class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t		m_szContentPath[255]; // �����쿡���� ��θ� 255���ڷ� ������

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};