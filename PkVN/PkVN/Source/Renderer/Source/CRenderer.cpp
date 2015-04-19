#include "..\Header\CRenderer.h"
#define SAFE_RELEASE(p) { if(p){ p->Release(); p = NULL; } }


CRenderer::CRenderer()
{
	m_pD3D = nullptr;				
	m_pDevice = nullptr;	
	
	m_pVertDecl = nullptr;	
	m_pVertBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	
	m_pEffect = nullptr;

	D3DXMatrixIdentity(&m_tTestMat);

	m_hWnd = nullptr;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;

	m_pCamera = nullptr;

	ZeroMemory(&m_tPresentParams,sizeof(D3DPRESENT_PARAMETERS));
};

CRenderer::~CRenderer()
{
	ShutDown();
};

void CRenderer::InitD3D(HWND window, int screenwidht, int screenheight, Camera* Camera)
{
	m_hWnd = window;
	m_nScreenHeight = screenheight;
	m_nScreenWidth = screenwidht;
	m_pCamera = Camera;
	//set present parameters
	ZeroMemory(&m_tPresentParams,sizeof(D3DPRESENT_PARAMETERS));
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	bool bWindowed = true;
	m_tPresentParams.hDeviceWindow					=		window;
	m_tPresentParams.Windowed						=		true;
	m_tPresentParams.BackBufferWidth				=		screenwidht;
	m_tPresentParams.BackBufferHeight				=		screenheight;
	m_tPresentParams.BackBufferCount				=		1;
	m_tPresentParams.BackBufferFormat				=		(bWindowed) ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8;
	m_tPresentParams.PresentationInterval			=		D3DPRESENT_INTERVAL_IMMEDIATE; //no VSync
	m_tPresentParams.SwapEffect					=		D3DSWAPEFFECT_DISCARD;
	m_tPresentParams.Flags							=		D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	m_tPresentParams.FullScreen_RefreshRateInHz	=		D3DPRESENT_RATE_DEFAULT;

	// add for 3D
	m_tPresentParams.EnableAutoDepthStencil = true;		// depth stencil
	m_tPresentParams.AutoDepthStencilFormat = D3DFMT_D16;	// stencil foramt

	HRESULT test = m_pD3D->CreateDevice(0, D3DDEVTYPE_HAL, window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_tPresentParams, &m_pDevice);
	//----------------------


	//set vertex declaration
	D3DVERTEXELEMENT9 decl[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};

	m_pDevice->CreateVertexDeclaration(decl, &m_pVertDecl);
	//----------------------


	//init effects
	ID3DXBuffer	*errors(NULL);

	D3DXCreateEffectFromFile(m_pDevice, "Pyramid.fx", 0, 0, D3DXSHADER_DEBUG, 0, &m_pEffect, &errors);
	if (errors)
	{
		MessageBox(m_hWnd,(char*)errors->GetBufferPointer(),0,0);
	}
	//----------------------
	InitTest();
};

void CRenderer::InitTest()
{
	//setting up verts for vertex buffer
	const int pnumverts = 5;
	vertex_poscol Pyr[pnumverts];
	
	Pyr[0].position = D3DXVECTOR3(-1.0f,-1.0f,-1.0f);
	Pyr[1].position = D3DXVECTOR3(0.0f,1.0f,0.0f);
	Pyr[2].position = D3DXVECTOR3(1.0f,-1.0f,-1.0f);
	Pyr[3].position = D3DXVECTOR3(1.0f,-1.0f,1.0f);
	Pyr[4].position = D3DXVECTOR3(-1.0f,-1.0f,1.0f);

	Pyr[0].color = D3DCOLOR_ARGB(255,0,0,255); //front left
	Pyr[1].color = D3DCOLOR_ARGB(255,255,0,255); //tip
	Pyr[2].color = D3DCOLOR_ARGB(255,0,255,0); //front right
	Pyr[3].color = D3DCOLOR_ARGB(255,255,0,0); //back right
	Pyr[4].color = D3DCOLOR_ARGB(255,0,255,255); //back left

	D3DXMatrixIdentity(&m_tTestMat);
	//----------------------------------

	//Create vertex buffer
	m_pDevice->CreateVertexBuffer(pnumverts*sizeof(vertex_poscol), 0, 0, D3DPOOL_DEFAULT, &m_pVertBuffer, 0);

	void *pbuffer;

	m_pVertBuffer->Lock(0,						
		pnumverts*sizeof(vertex_poscol),	//8 or 36
		&pbuffer,							
		D3DLOCK_DISCARD);					

	memcpy(pbuffer, Pyr, pnumverts*sizeof(vertex_poscol));
	m_pVertBuffer->Unlock();
	//----------------------------------

	//set up index buffer
	WORD ipL[18];
	ipL[0] = 2; //front left
	ipL[1] = 0; //tip
	ipL[2] = 1; //front right

	ipL[3] = 1;
	ipL[4] = 3; //back right
	ipL[5] = 2;

	ipL[6] = 3;
	ipL[7] = 1; //back left
	ipL[8] = 4;

	ipL[9] = 4;
	ipL[10] = 1;
	ipL[11] = 0;

	ipL[12] = 0;
	ipL[13] = 3;
	ipL[14] = 4;

	ipL[15] = 0;
	ipL[16] = 2;
	ipL[17] = 3;
	//----------------------------------

	//create index buffer
	m_pDevice->CreateIndexBuffer(18 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);
	m_pIndexBuffer->Lock(0, 18 * sizeof(WORD), &pbuffer, 0);
	memcpy(pbuffer, ipL, 18 * sizeof(WORD));
	m_pIndexBuffer->Unlock();
	//----------------------------------
};

void CRenderer::Render(float fDt)
{
	//clear
	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128,128,255), 1.0f, 0);	// modify for zbuffer
	
	m_pDevice->BeginScene();

	//draw stuff
	DrawTest();

	m_pDevice->EndScene();
	m_pDevice->Present(0,0,0,0);
};

void CRenderer::DrawTest()
{
	if(m_pEffect)
	{

		m_pEffect->SetTechnique("Basic");

		unsigned passes(0);
		m_pEffect->Begin(&passes, 0);

		for(unsigned i(0); i<passes; ++i)
		{
			m_pEffect->BeginPass(i);
			{
				m_tTestMat._11 = 3; m_tTestMat._22 = 3; m_tTestMat._33 = 3;
				float colors[4];
				colors[0] = rand() % 255; colors[1] = rand() % 255; colors[2] = rand() % 255; colors[3] = rand() % 255;
				colors[0] = colors[0]/255.0f; colors[1] = colors[1]/255.0f; colors[2] =colors[2]/255.0f; colors[3] = colors[3]/255.0f;
				float gCol[4];
				gCol[0] = 0.0f; gCol[1] = 255.0f; gCol[2] = 0.0f; gCol[3] = 1.0f;
				m_pEffect->SetFloatArray("gCol",gCol,4);
				m_pEffect->SetFloatArray("cola",colors,4);
				m_pEffect->SetMatrix("gWVP", &(m_tTestMat * m_pCamera->GetViewMatrix() * m_pCamera->GetProjectionMatrix() ));
				m_pEffect->CommitChanges();

				m_pDevice->SetVertexDeclaration(m_pVertDecl);
				m_pDevice->SetStreamSource(0,m_pVertBuffer, 0,sizeof(vertex_poscol));
				
				m_pDevice->SetIndices(m_pIndexBuffer);
				
				m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,18,0,6);

			}
			m_pEffect->EndPass();
		}
		m_pEffect->End();
	}
};

void CRenderer::ShutDown()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pVertBuffer);
	SAFE_RELEASE(m_pIndexBuffer);

	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D);
};
