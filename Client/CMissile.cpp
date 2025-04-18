#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta((45.f / 180.f) * PI)
	, m_vDir(Vec2(0.f, 1.f))
{
	m_vDir.Normalize();
}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	// vPos.x += 600.f * cosf(m_fTheta) * fDT;
	// vPos.y -= 600.f * sinf(m_fTheta) * fDT; 윈도우 좌표에선 y축의 +가 아래를 가리키기 때문에 - 연산

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}

// 1라디안
// 반지름의 길이가 r인 원에서 길이가 r인 호에 대한 중심각의 크기를 α 라고 했을 때 α 의 크기
// r : 2πr = αº : 360º
// ∴ αº = 180º / π

// 삼각함수 Θ = radian
// cosΘ : 밑변 / 빗변 (x 좌표)
// sinΘ : 높이 / 빗변 (y 좌표)
// tanΘ : 높이 / 밑변 => 직선의 방정식에선 기울기를 뜻함

// 벡터
// 빗변의 길이를 1로 만들었을 때 밑변과 높이를 구하여 x, y 좌표 적용