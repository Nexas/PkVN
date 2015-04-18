#include "../Header/CGame.h"
#include <ctime>
//#include "../../States/Header/IBaseState.h"
//#include "CMainMenuState.h"
//#include "COptionsState.h"

CGame::CGame()
{
	/*m_pD3D	=  nullptr;
	m_pTM	=  nullptr;
	m_pFM	=  nullptr;
	m_pDI	=  nullptr;
	m_nImageID = -1;
	m_nSoundID = -1;
	//currentState = nullptr;*/
	Windowed = true;
	m_fGameTime = 0.0f;
}

CGame::~CGame()
{

}

CGame* CGame::GetInstance()
{
	// Lazy instantiation
	static CGame ptr;
	return &ptr;
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	// Get Singleton Pointers:
	/*m_pD3D	=  CSGD_Direct3D::GetInstance();
	m_pTM	=  CSGD_TextureManager::GetInstance();
	m_pFM	=  CSGD_FModManager::GetInstance();
	m_pDI	=  CSGD_DirectInput::GetInstance();

	// Initialize Singletons:
	m_pD3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, true);
	Windowed = bIsWindowed;
	m_pTM->InitTextureManager(m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite());
	m_pFM->InitFModManager(hWnd);
	m_pDI->InitDirectInput(hWnd, hInstance, DI_KEYBOARD | DI_MOUSE, 0);

	ChangeState(CMainMenuState::GetInstance());*/
	//currentState->Enter();
	srand(unsigned int(time(0)));
	m_stopWatch.Start();
}

void CGame::Shutdown()
{
	//ChangeState(nullptr);

	// Shutdown in the opposite order you initialized
	/*if (m_pDI)
	{
		m_pDI->ShutdownDirectInput();
		m_pDI = NULL;
	}

	if (m_pFM)
	{
		m_pFM->ShutdownFModManager();
		m_pFM = NULL;
	}

	if (m_pTM)
	{
		m_pTM->ShutdownTextureManager();
		m_pTM = NULL;
	}

	if (m_pD3D)
	{
		m_pD3D->ShutdownDirect3D();
		m_pD3D = NULL;
	}*/
}

bool CGame::Main()
{
	// Get Elapsed Time
	m_fElapsedTime = (float)m_stopWatch.GetElapsedTime();

	m_stopWatch.Reset();

	// The 3 steps a game does during EXECUTION:
	// Input
	if (Input() == false)
		return false;
	// Update
	Update();
	// Draw
	Render();
	return true;
}

bool CGame::Input()
{
	/*m_pDI->ReadDevices(); // usually called ONCE a frame


	if ((m_pDI->KeyDown(DIK_LALT) && m_pDI->KeyPressed(DIK_RETURN)) || (m_pDI->KeyDown(DIK_RALT) && m_pDI->KeyPressed(DIK_RETURN)))
	{
		m_pDI->ReadDevices();
		Windowed = !Windowed;
		m_pD3D->ChangeDisplayParam(m_pD3D->GetPresentParams()->BackBufferWidth, m_pD3D->GetPresentParams()->BackBufferHeight, Windowed);
	}

	//if (m_pDI->KeyPressed(DIK_ESCAPE))
	//{
	//	return false;
	//}

	if (m_pvStates.top()->Input() == false)
	{
		return false;
	}

	//if(currentState->Input() == false)
	//{
	//	return false;
	//	//PostQuitMessage(0);
	//}
	*/
	return true;
}

void CGame::Update()
{
	m_fElapsedTime = m_stopWatch.GetElapsedTime();
	//m_pFM->Update(); // update all sounds

	//m_pvStates.top()->Update(m_fElapsedTime);
	//currentState->Update(m_fElapsedTime);
}

void CGame::Render()
{
	/*m_pD3D->Clear(255, 0, 0);
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();

	//currentState->Render();
	m_pvStates.top()->Render();

	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();
	m_pD3D->Present();*/
}

void CGame::PushState(IBaseState* _state)
{
	/*if (_state)
	{
		m_pvStates.push(_state);
		m_pvStates.top()->Enter();
	}*/
}

void CGame::PopState(void)
{
	/*if (m_pvStates.size() > 0)
	{
		m_pvStates.top()->Exit();
		m_pvStates.pop();
	}*/
}

void CGame::ClearAllStates(void)
{
	/*unsigned int stackSize = m_pvStates.size();
	for (unsigned int i = 0; i < stackSize; ++i)
	{
		m_pvStates.top()->Exit();
		m_pvStates.pop();
	}*/
}

void CGame::ChangeState(IBaseState* _currentState)
{
	/*ClearAllStates();
	if (_currentState)
		PushState(_currentState);
		*/
}
