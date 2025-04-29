#pragma once

// ���漱�� => �������� �ӵ��� ������ ���� �ʱ� ����, ������Ʈ �� �ڵ尡 ����� �� �Ź� �˻�(����)�� �ʿ䰡 ����
class CObject;

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;						// Scene �̸�

	UINT				m_iTileX;	// Ÿ�� ���� ����	
	UINT				m_iTileY;	// Ÿ�� ���� ����

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual void update(); // ������Ʈ ������Ʈ
	virtual void finalupdate(); // �� �� �۾��� ���������ִ� ������Ʈ
	virtual void render(HDC _dc);

	// ���� �����Լ�, �θ� Ŭ������ �ش��ϴ� ���� ���� ��ü������ �Ұ������� => �߻� Ŭ����
	virtual void Enter() = 0; // �ش� Scene �� ���� �� ȣ��
	virtual void Exit() = 0;  // �ش� Scene �� Ż�� �� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) // Ŭ������ ����� �����ϸ� �Լ� ȣ�� ����� ��°��� �ƴ� ���� �ٿ��ֱ� ȿ��
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void CreateTile(UINT _iXCount, UINT _iYCount);

	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	CScene();
	virtual ~CScene();
};

