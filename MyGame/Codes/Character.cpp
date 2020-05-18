#include "stdafx.h"
#include "..\Headers\Character.h"
#include "Stat.h"
#include "Clock.h"
#include "Shader.h"
#include "StateCon.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "TimerMgr.h"

USING(MyGame)



//VIBUffer 복사하는 코드 지움
CCharacter::CCharacter(CCharacter & _character)
	:CGameObject(_character),
	m_tStat(_character.m_tStat),
	m_vecImmune(_character.m_vecImmune)
{
}

_int CCharacter::StartAct()
{
	return m_pStateCon->Start(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));
}

_int CCharacter::UpdateAct()
{
	return m_pStateCon->Update(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));
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
	{
		if (nullptr == m_pTransform)
			return;

		//m_pTransform->Stop();

		OnTakeDamage();
	}

}

void CCharacter::Heal(_float _healAmount)
{
	m_tStat.m_fHP += _healAmount;
	if (m_tStat.m_fHP >= m_tStat.m_fMaxHp->GetValue())
		m_tStat.m_fHP = m_tStat.m_fMaxHp->GetValue();
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

_int CCharacter::Interact(CGameObject * _pOther)
{
	if (nullptr == m_pTransform		||
		nullptr == _pOther)
		return -1;

	//상대방이 캐릭터면 상대방에게 데미지를 줌
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	if (nullptr != pCharacter)
	{
		pCharacter->TakeDamage(m_tStat.m_fAtt->GetValue());

		CTransform* pOtherTransform = (CTransform*)_pOther->Get_Module(L"Transform");
		if (nullptr == pOtherTransform)return -1;

		//피 파티클 생성
		Vector3 vPos = m_pTransform->Get_Position();
		CParticleSystem::STATEDESC desc;
		desc.m_tBaseDesc.vPos = pOtherTransform->Get_Position();
		desc.m_pTextureTag = L"Blood";
		desc.m_eTextureSceneID = SCENE_STAGE;
		desc.m_dDuration = 0.2f;
		desc.m_dLifeTime = 0.2f;
		desc.m_fSpeed = 300.f;
		desc.m_vParticleSize = Vector2(10.f, 10.f);
		CObjMgr* pObjMgr = CObjMgr::Get_Instance();
		CParticleSystem* pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STAGE, L"ParticleSystem", SCENE_STAGE, &desc));

		
		Vector2 vDir =  pOtherTransform->Get_Position() - m_pTransform->Get_Position();

		//피가 튀긴다.
		pParticleSystem->Spread(vDir, CTimerMgr::Get_Instance()->Get_TimeDelta(), 5);
	}
	return 0;
}

HRESULT CCharacter::Get_TerrainIndex(pair<_int, _int>& _out)
{
	if (nullptr == m_pTransform)
		return E_FAIL;
	_int x = (_int)m_pTransform->Get_Position().x / TILECX;
	_int y = (_int)m_pTransform->Get_Position().y / TILECY;

	_out.first = x;
	_out.second = y;

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
	if (FAILED(Get_TerrainIndex(vMyTerrainIndex)))
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

void CCharacter::OnCollisionEnter(CGameObject * _pOther)
{
	//if (nullptr != dynamic_cast<CCharacter*>(_pOther))
	//{
	//	m_pTransform->Stop();
	//}
}



void CCharacter::OnDead()
{
}

void CCharacter::OnTakeDamage()
{
	//반짝거림
	m_iPass = 3;


}

void CCharacter::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pStateCon);
	Safe_Release(m_pShader);
	m_tStat.Free();

	CGameObject::Free();
}
