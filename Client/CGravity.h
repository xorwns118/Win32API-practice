#pragma once

class CObject;

class CGravity
{
private:
	CObject*	m_pOwner;

	bool		m_bGround;

public:
	void SetGround(bool _b);

public:
	void finalupdate();

public:
	CGravity();
	CGravity(const CGravity& _origin);
	~CGravity();

	friend class CObject;
};

