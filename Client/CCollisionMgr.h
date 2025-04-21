#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	// �浹ü ���� ���� ������ �浹 ����

	UINT	m_arrCheck[(UINT)GROUP_TYPE::END];	// �׷���� �浹 üũ ��Ʈ����

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); } // memset() ������ �ּҸ� ������ ������ ���� (byte ������)

private:
	void CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

};

