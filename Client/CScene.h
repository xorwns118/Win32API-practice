#pragma once

// 전방선언 => 컴파일의 속도에 영향을 주지 않기 위함, 오브젝트 쪽 코드가 변경될 시 매번 검사(대응)할 필요가 없음
class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName;						  // Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update(); // 오브젝트 업데이트
	void finalupdate(); // 그 외 작업을 마무리해주는 업데이트
	void render(HDC _dc);

	// 순수 가상함수, 부모 클래스에 해당하는 씬은 직접 객체생성이 불가능해짐 => 추상 클래스
	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0;  // 해당 Scene 을 탈출 시 호출

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // 클래스는 헤더에 구현하면 함수 호출 비용이 드는것이 아닌 복사 붙여넣기 효과
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

public:
	CScene();
	virtual ~CScene();
};

