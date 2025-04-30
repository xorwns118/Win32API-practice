#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{

}

void CTile::render(HDC _dc)
{
	if (m_pTileTex == nullptr || m_iImgIdx == -1)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE; // 640 -> 10
	UINT iMaxRow = iHeight / TILE_SIZE; // 1152 -> 18

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol; // 181 / 10 = 18
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol; // 181 % 10 = 1

	if (iCurRow >= iMaxRow)
	{
		assert(nullptr);
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc
		, (int)(vRenderPos.x)
		, (int)(vRenderPos.y)
		, (int)(vScale.x)
		, (int)(vScale.y)
		, m_pTileTex->GetDC()
		, (int)(iCurCol * TILE_SIZE)
		, (int)(iCurRow * TILE_SIZE)
		, SRCCOPY);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}
