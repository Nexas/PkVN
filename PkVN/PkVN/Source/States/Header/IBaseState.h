//#ifndef IBASESTATE_H_
//#define IBASESTATE_H_
#pragma once
/*#include "../../Wrappers/Header/CSGD_Direct3D.h"
#include "../../Wrappers/Header/CSGD_DirectInput.h"
#include "../../Wrappers/Header/CSGD_FModManager.h"
#include "../../Wrappers/Header/CSGD_TextureManager.h"*/

class IBaseState
{

protected:
	int m_nBGMVol;
	int m_nSFXVol;
	int m_nPan;
	/*CSGD_Direct3D*			m_pD3D;
	CSGD_TextureManager*	m_pTM;
	CSGD_FModManager*		m_pFM;
	CSGD_DirectInput*		m_pDI;*/

public:
	IBaseState() {m_nBGMVol = 50; m_nSFXVol = 50; m_nPan = 50;}
	//virtual IBaseState(void) = 0;
	virtual ~IBaseState(void) = 0 {}
	virtual void Enter() = 0;
	virtual bool Input() = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

//#endif /*IBASESTATE_H_*/