#pragma once

// ���漱�� => �������� �ӵ��� ������ ���� �ʱ� ����, ������Ʈ �� �ڵ尡 ����� �� �Ź� �˻�(����)�� �ʿ䰡 ����
class CObject;

class CScene
{
private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring			 m_strName;						  // Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update(); // ������Ʈ ������Ʈ
	void finalupdate(); // �� �� �۾��� ���������ִ� ������Ʈ
	void render(HDC _dc);

	// ���� �����Լ�, �θ� Ŭ������ �ش��ϴ� ���� ���� ��ü������ �Ұ������� => �߻� Ŭ����
	virtual void Enter() = 0; // �ش� Scene �� ���� �� ȣ��
	virtual void Exit() = 0;  // �ش� Scene �� Ż�� �� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // Ŭ������ ����� �����ϸ� �Լ� ȣ�� ����� ��°��� �ƴ� ���� �ٿ��ֱ� ȿ��
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

public:
	CScene();
	virtual ~CScene();
};

