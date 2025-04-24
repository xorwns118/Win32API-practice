#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;		// 좌상단 위치
	Vec2	vSlice;		// 자를 사이즈 영역
	Vec2	vOffset;
	float	fDuration;	// 시간
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		// Animation 이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;	// 모든 프레임 정보
	int					m_iCurFrm;	// 현재 프레임
	float				m_fAccTime; // 시간 누적
	
	bool				m_bFinish;	// 재생 끝 도달 여부

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; } // 받아간 쪽에서 수정할 수 있게 래퍼런스타입 
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

