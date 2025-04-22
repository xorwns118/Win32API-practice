#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;	// Large_Integer => union
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			// 프레임 간의 시간 값 (Delta Time)
	double			m_dAcc;			// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 함수 호출 횟수 체크
	UINT			m_iFPS;			// 초당 호출 횟수

	// FPS
	// 1프레임당 시간, (Delta Time)
	
public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};
