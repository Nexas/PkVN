/////////////////////////////////////////////
// File Name: "CGame.h"
//
// Author Name: Sean Welch
//
// Purpose: To contain all game related code.
/////////////////////////////////////////////

// Cross compiler
// Works on Borland, CodeWarrior, etc.
#ifndef CGAME_H_
#define CGAME_H_
/*#include "../../Wrappers/Header/CSGD_Direct3D.h"
#include "../../Wrappers/Header/CSGD_DirectInput.h"
#include "../../Wrappers/Header/CSGD_FModManager.h"
#include "../../Wrappers/Header/CSGD_TextureManager.h"
//#include "CStopWatch.h"
#include "../../States/Header/CMainMenuState.h"*/
#include "../../States/Header/IBaseState.h"
#include "../../Util/Header/CTimer.h"
#include "../../Renderer/Header/CRenderer.h"
#include "../../Renderer/Header/Camera.h"
#include "../../Util/Header/SeW_DirectInput.h"
#include "../../Util/Header/CScriptingSystem.h"

#include <stack>

using namespace std;

//class IBaseState;
//class CMainMenuState;
// Define class here
class CGame
{
private:
	// Singleton pointers:
	/*CSGD_Direct3D*			m_pD3D;
	CSGD_TextureManager*	m_pTM;
	CSGD_FModManager*		m_pFM;
	CSGD_DirectInput*		m_pDI;
	//IBaseState* currentState;
	stack<IBaseState*> m_pvStates;

	//CStopWatch	m_stopWatch;
	
	
	

	
	// Asset ids:
	int m_nImageID;
	int m_nSoundID;*/
	CSeW_DirectInput*	m_pDI;
	bool Windowed;
	CTimer			m_stopWatch;
	float		m_fElapsedTime;
	float		m_fGameTime;
	Camera* m_pCamera;
	CRenderer* m_pRenderer;
	// Proper Singleton:

	// Constructor
	CGame();

	// Trilogy of Evil:
	// destructor
	~CGame();
	// copy constructor
	CGame(const CGame& c);
	// Assignment operator
	CGame &operator=(const CGame& c);

public:
	// Singleton accessor
	static CGame* GetInstance();

	// 3 sterps a game goes through during it's LIFETIME:
	// Initialize
	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);
	// Execution (returns false if the application should quit)
	bool Main();
	// Cleanup
	void Shutdown();

	bool Input();
	void Update();
	void Render(float fDt);
	void PushState(IBaseState* _state);
	void PopState(void);
	void ClearAllStates(void);
	void ChangeState(IBaseState* _currentState);
};

#endif