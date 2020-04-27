#pragma once
#include "GameObject.h"

BEGIN(MyGame)
class CStat;
class CClock_Single;
class CTransform;
class CVIBuffer;
class CTexture;
class CCharacter abstract : public CGameObject
{
protected:
	explicit CCharacter(PDIRECT3DDEVICE9 _pGraphic_Device) :CGameObject(_pGraphic_Device){};
	explicit CCharacter(CCharacter& _character) :CGameObject(_character) {}
	virtual ~CCharacter() = default;

protected:
	typedef struct tagStat
	{
		float	m_fHP;
		CStat*	m_pMaxHp;
		CStat*	m_pArmor;
		CStat*	m_pAtt;
		int		m_iGold;
		float	m_fExp;
		float	m_fMaxExp;
	}STAT;

	//저항
	enum IMMUNE {IMMUNE_FIRE, IMMUNE_ICE, IMMUNE_END};

protected:
	CTransform*	m_pTransform;
	CVIBuffer*	m_pVIBuffer;

protected:
	STAT	m_tStat = {};
	vector<IMMUNE> m_vecImmune;
	
	float	m_fSpeed = 0.f;

	bool	m_bDead = false;
	bool	m_bInvisible = false;
	//이동할 목표지점
	Vector4			m_vDst = {};

	


public:
	virtual void TakeDamage(float _fDamage);
	void SetInvisible(bool _bInvisible) { m_bInvisible = _bInvisible; }
	bool IsAlive();
	bool IsImmune(IMMUNE _eImmune);
	


protected:
	//해당 좌표로 이동한다.
	HRESULT MoveToDst(Vector4 _vDst, _double _timeDelta);
	virtual void Process() = 0;
	virtual void Update_State() = 0;
	virtual void OnDead() = 0;
	virtual void OnTakeDamage() = 0;
	virtual void Scene_Change() = 0;

protected:
	void MoveFrame();

public:
	virtual void Free() override;
};

END