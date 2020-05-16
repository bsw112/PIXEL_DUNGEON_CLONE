#pragma once

#include "GameObject.h"
BEGIN(MyGame)

class CVIBuffer;
class CTexture;
class CTransform;
class CShader;
//이미지와 버튼은 프로토타입을 만들기 싫다. 딱히 재활용안하니까.
class CImage : public CGameObject
{
protected:
	explicit CImage(PDIRECT3DDEVICE9 _pGraphic_Device) : CGameObject(_pGraphic_Device) 
	{
		int aa = 0;
		int b = 0;
	}
	explicit CImage(CImage& _rhs);
	virtual ~CImage() = default;

protected:
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTextrue = nullptr;
	CTransform*	m_pTransform = nullptr;
	CShader*	m_pShader = nullptr;
	const _tchar*	m_pTextureTag = L"";
	_int			m_iTextureID = 1;
	MYFONT			m_tFont;

public:
	virtual HRESULT Initialize(_tchar* _pTextureTag, Vector4 _vPos, Vector2 _vSize, SCENEID _eTextureSceneID);
	virtual _int Update(_double _timeDelta) override;
	virtual _int LateUpate(_double _timeDelta) override;
	virtual HRESULT Render() override;

protected:
	virtual HRESULT	OnRender();

public:
	void	Set_Font(MYFONT _tFont) { m_tFont = _tFont; }
	void	Replace_Texture(const _tchar* pTextureTag, _int _iTextureID, SCENEID _eTextureSceneID);
public:
	static CImage* Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual	CGameObject* Clone(void* _param = nullptr)override;
	virtual void Free() override;

};
END
