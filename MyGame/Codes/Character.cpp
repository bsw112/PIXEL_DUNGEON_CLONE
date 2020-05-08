#include "stdafx.h"
#include "..\Headers\Character.h"
#include "Stat.h"
#include "Clock.h"

USING(MyGame)




CCharacter::CCharacter(CCharacter & _character)
	:CGameObject(_character),
	m_tStat(_character.m_tStat),
	m_pVIBuffer(_character.m_pVIBuffer),
	m_vecImmune(_character.m_vecImmune)
{
}

void CCharacter::TakeDamage(float _fDamage)
{

	m_tStat.m_fHP -= _fDamage;

	if (m_tStat.m_fHP < 0)
	{
		OnDead();
		m_tStat.m_fHP = 0.f;
	}
	else
		OnTakeDamage();

}


bool CCharacter::IsAlive()
{
	return m_tStat.m_fHP > 0;
}

bool CCharacter::IsImmune(IMMUNE _eImmune)
{
	for (auto& immune : m_vecImmune)
	{
		if (immune == _eImmune)
			return true;
	}
	return false;
}

HRESULT CCharacter::Get_TerrainIndex(pair<_int,_int>& _out)
{	
	if (nullptr == m_pTransform)
		return E_FAIL;
	 _int x = (_int)m_pTransform->Get_Position().x / TILECX;
	 _int y = (_int)m_pTransform->Get_Position().y / TILECY;
	
	_out.first	= x;
	_out.second	= y;

	return S_OK;
}

bool CCharacter::IsTargetInRange(CCharacter * pTarget, _int _iRange)
{
	if (nullptr == pTarget)
		return false;

	pair<_int, _int> vTargetTerrainIndex;
	if (FAILED(pTarget->Get_TerrainIndex(vTargetTerrainIndex)))
		return false;

	pair<_int, _int> vMyTerrainIndex;
	if(FAILED(Get_TerrainIndex(vMyTerrainIndex)))
		return false;

	//타깃이 범위안에 들어오면
	if (vTargetTerrainIndex.first >= vMyTerrainIndex.first - _iRange && vTargetTerrainIndex.first <= vMyTerrainIndex.first + _iRange)
	{
		if (vTargetTerrainIndex.second >= vMyTerrainIndex.second - _iRange && vTargetTerrainIndex.second <= vMyTerrainIndex.second + _iRange)
		{
			return true;
		}
	}
	return false;
}



void CCharacter::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);

	CGameObject::Free();
}
