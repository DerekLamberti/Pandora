#pragma once

//#include "InputTracker.h"

#include "WorldBuilderGui.h"

#include <d3d11.h>

namespace Pandora
{

class InputTracker;
class ImGuiWrapperD3D11 : public WorldBuilderGui
{
public:
	ImGuiWrapperD3D11()
		: m_Device(nullptr)
		, m_DeviceContext(nullptr)
		//,	m_hWnd(nullptr)
		, m_pVB(nullptr)
		, m_pIB(nullptr)
		, m_pVertexShaderBlob(nullptr)
		, m_pVertexShader(nullptr)
		, m_pInputLayout(nullptr)
		, m_pVertexConstantBuffer(nullptr)
		, m_pPixelShaderBlob(nullptr)
		, m_pPixelShader(nullptr)
		, m_pFontSampler(nullptr)
		, m_pFontTextureView(nullptr)
		, m_pRasterizerState(nullptr)
		, m_pBlendState(nullptr)
		, m_pDepthStencilState(nullptr)
		, m_VertexBufferSize(5000)
		, m_IndexBufferSize(10000)
	{}

	bool Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hWnd);
	void ReleaseResources();

	bool CreateFonts();

	void Render();



private:
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	HWND					m_hWnd;

	ID3D11Buffer*            m_pVB = NULL;
	ID3D11Buffer*            m_pIB = NULL;
	ID3D10Blob *             m_pVertexShaderBlob = NULL;
	ID3D11VertexShader*      m_pVertexShader = NULL;
	ID3D11InputLayout*       m_pInputLayout = NULL;
	ID3D11Buffer*            m_pVertexConstantBuffer = NULL;
	ID3D10Blob *             m_pPixelShaderBlob = NULL;
	ID3D11PixelShader*       m_pPixelShader = NULL;
	ID3D11SamplerState*      m_pFontSampler = NULL;
	ID3D11ShaderResourceView*m_pFontTextureView = NULL;
	ID3D11RasterizerState*   m_pRasterizerState = NULL;
	ID3D11BlendState*        m_pBlendState = NULL;
	ID3D11DepthStencilState* m_pDepthStencilState = NULL;

	int m_VertexBufferSize;
	int m_IndexBufferSize;
};

} // namespace Pandora