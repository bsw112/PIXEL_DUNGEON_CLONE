#pragma once
#include "Character.h"

BEGIN(MyGame)

class CAiState;
class CMonster abstract : public CCharacter
{

protected:
	explicit CMonster(PDIRECT3DDEVICE9 _pGraphic_Device) :CCharacter(_pGraphic_Device) {};
	explicit CMonster(CMonster& _rhs);
	virtual ~CMonster() = default;


protected:
	CAiState* m_pSLEEPING	= nullptr;
	CAiState* m_pHUNTING	= nullptr;
	CAiState* m_pWANDERING	= nullptr;
	CAiState* m_pCurState	= nullptr;


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;









};
END
