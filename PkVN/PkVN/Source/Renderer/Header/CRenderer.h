#ifndef CRENDERER_H
#define CRENDERER_H
#include <d3d9.h>
#include <d3dx9.h>
#include "../Header/Camera.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


class CRenderer
{
private:
	IDirect3D9*						m_pD3D;					
	IDirect3DDevice9*				m_pDevice;	


	IDirect3DVertexDeclaration9*	m_pVertDecl;	
	IDirect3DVertexBuffer9*			m_pVertBuffer;
	IDirect3DIndexBuffer9*			m_pIndexBuffer;

	Camera*							m_pCamera;

	IDirect3DTexture9*				m_pTestTextrue;

	ID3DXEffect*					m_pEffect;

	D3DXMATRIX						m_tTestMat;

	HWND							m_hWnd;
	int								m_nScreenWidth;
	int								m_nScreenHeight;

	D3DPRESENT_PARAMETERS			m_tPresentParams;
public:
	struct vertex_poscol
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
		D3DXVECTOR2 texcords;
	};

	CRenderer();
	~CRenderer();
	//hWnd,nScreenWidth,nScreenHeight
	void InitD3D(HWND window, int screenwidht, int screenheight, Camera* Camera);
	void ShutDown();
	void Render(float fDt);
	void InitTest();
	void DrawTest();

};

#endif