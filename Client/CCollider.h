#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject*	m_pOwner;		// collider �� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;	// ������Ʈ�� ���� ������� ��ġ��
	Vec2		m_vFinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	Vec2		m_vScale;		// �浹ü�� ũ��

	UINT		m_iID;			// �浹ü ���� ������ ID ��

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vPos) { m_vScale = _vPos; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	CCollider();
	~CCollider();

	friend class CObject;
};

