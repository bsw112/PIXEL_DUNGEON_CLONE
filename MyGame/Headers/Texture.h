#pragma once
#include "Module.h"

BEGIN(MyGame)
//텍스쳐클래스는 여러개의 텍스쳐를 포함할 수 있다. 
//애니메이션 클립처럼도 쓸 수 있다.
class CShader;
class CTexture final : public CModule
{
private:
	explicit CTexture(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	explicit CTexture(CTexture& _rhs);
	virtual ~CTexture() = default;

private:
	vector<LPDIRECT3DTEXTURE9> m_vecTexture;
public:
	virtual HRESULT Initialize_Prototype(const _tchar* _pFilePath, _uint _iCnt);
	virtual HRESULT Initialize_Prototype(LPDIRECT3DTEXTURE9 _pTexture);

	virtual HRESULT Initialize(void* _pArg);

public:
	HRESULT Set_Texture(_uint _iIndex);
	HRESULT Set_TextureOnShader(CShader* _pShader, D3DXHANDLE hParameter, _uint _iTextureIndex);
	size_t	Get_TextureSize() { return m_vecTexture.size(); }
	
	

public:
	static CTexture* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _tchar* _pFilePath, _uint _iCnt = 1);
	static CTexture* Create(PDIRECT3DDEVICE9 _pGraphic_Device, LPDIRECT3DTEXTURE9 _pTexture);
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free();
};
END
