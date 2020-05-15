#include "stdafx.h"
#include "..\Headers\AIState.h"
#include "Character.h"
#include "ObjMgr.h"

USING(MyGame)

CAIState::STATE CAIIdle::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (_isAlerted)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
		if (nullptr == pTargetTransform)
			return STATE_END;




		return STATE_HUNTING;
	}

	return STATE_END;
}

CAIState::STATE CAIIdle::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_IDLE;
}

void CAIIdle::Free()
{
}



CAIState::STATE CAISleeping::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (_isAlerted)
	{
		return STATE_HUNTING;
	}
	return STATE_END;
}

CAIState::STATE CAISleeping::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{

	CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
	if (nullptr == pAnimator)
		return STATE_END;

	pAnimator->Play(L"Sleep");


	return STATE_END;
}

void CAISleeping::Free()
{
}

CAIState::STATE CAIHunting::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	if (!_isAlerted)
		return STATE_IDLE;

	//이동력만큼 이동했으면 턴을 끝낸다.
	if (pTransform->Is_TurnEnd())
	{
		return STATE_HUNTING;
	}

	return STATE_END;
}

CAIState::STATE CAIHunting::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	if (nullptr == m_pActor)
		return STATE_END;

	CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
	if (nullptr == pTransform)
		return STATE_END;

	//트랜스폼에게 다시 이동한 타일 수를 세라고 함.
	pTransform->NextTurn();

	if (_canAttack)
	{
		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		//공격
		pFocus->TakeDamage(m_pActor->Get_Stat().m_fAtt->GetValue());

		//공격 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;

		pAnimator->Play(L"attack");
	}
	else if (_isAlerted)
	{
		CTransform* pTransform = (CTransform*)m_pActor->Get_Module(L"Transform");
		if (nullptr == pTransform)
			return STATE_END;

		CCharacter* pFocus = m_pActor->Get_Focus();
		if (nullptr == pFocus)
			return STATE_END;

		CTransform* pTargetTransform = (CTransform*)pFocus->Get_Module(L"Transform");
		if (nullptr == pTargetTransform)
			return STATE_END;

		//점프 모션
		CAnimator*	pAnimator = (CAnimator*)m_pActor->Get_Module(L"Animator");
		if (nullptr == pAnimator)
			return STATE_END;
		pAnimator->Play(L"walk");

		//타깃을 향해 간다.
		pTransform->Go_Target(pTargetTransform, 1.f);
	}
	return STATE_END;
}

void CAIHunting::Free()
{
}

CAIState::STATE CAIWandering::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

CAIState::STATE CAIWandering::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return STATE_END;
}

void CAIWandering::Free()
{
}


CAIState::STATE CAIHunting_Jump::LateUpdate(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return CAIHunting::LateUpdate(_canAttack, _isAlerted, _timeDelta);
}

CAIState::STATE CAIHunting_Jump::Act(_bool _canAttack, _bool _isAlerted, _double _timeDelta)
{
	return CAIHunting::Act(_canAttack, _isAlerted, _timeDelta);
}

void CAIHunting_Jump::Free()
{
}

