#pragma once

// 1. 프레임 동기화, 어떤 키의 반응에 대해 눌린 시점과 떨어진 시점이 일치하지 않을 때 수행되어야 할 함수가 실행되지 않는 것을 방지
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가진다.

// 2. 키 입력 이벤트 처리
// tap, hold, away

enum class KEY_STATE
{
	NONE,	// 눌리지 않고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는 시점
	AWAY,	// 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST, // enum의 끝
};

struct tKeyInfo
{
	KEY_STATE	eState;		// 키의 상태값
	bool		bPrevPush;	// 이전 프레임에서 눌렸는지의 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
};

