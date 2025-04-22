#pragma once

#include "CCollider.h"

class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;

	bool		m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

	bool IsDead() { return !m_bAlive; }

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

public:
	virtual void update() = 0;
	virtual void finalupdate() final; // => final 키워드 : 여기까지가 마지막이고, 그 아래의 오버라이딩 함수는 무시함. (자식 클래스에서 재정의 불가)
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

private:
	void SetDead() { m_bAlive = false; }

public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};