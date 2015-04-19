/**************************************************************
* File: Camera.h
*
* Author: Sean Welch
*
* Last Modified: 5/28/2013
*
* Date Created:  5/28/2013
*
* Purpose: To be a camera.
***************************************************************/
#ifndef CAMERA_H_
#define CAMERA_H_

// Including the header files for Direct3D9.
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
	D3DXMATRIX m_tViewMatrix;
	D3DXMATRIX m_tProjMatrix;

public:

	Camera(void);
	~Camera(void);

	/****************************************
	* ACCESSORS
	****************************************/
	D3DXMATRIX GetViewMatrix(bool bTranslate = true);
	D3DXMATRIX GetProjectionMatrix()										{return m_tProjMatrix;}
	D3DXVECTOR3 GetViewXAxis();
	D3DXVECTOR3 GetViewYAxis();
	D3DXVECTOR3 GetViewZAxis();
	D3DXVECTOR3 GetViewPos();


	/****************************************
	* MUTATORS
	****************************************/
	void SetViewMatrix(D3DXMATRIX* pMat)									{m_tViewMatrix = *pMat;}
	void SetProjectionMatrix(D3DXMATRIX* pMat)								{m_tProjMatrix = *pMat;}
	void SetViewXAxis(float x, float y, float z);
	void SetViewXAxis(D3DXVECTOR3 tVec);
	void SetViewYAxis(float x, float y, float z);
	void SetViewYAxis(D3DXVECTOR3 tVec);
	void SetViewZAxis(float x, float y, float z);
	void SetViewZAxis(D3DXVECTOR3 tVec);
	void SetViewPos(float x, float y, float z);
	void SetViewPos(D3DXVECTOR3 tVec);


	void BuildProjectionMatrix(float fFoV, float fAspectRatio, float fNearPlane, float fFarPlane);

	/*****************************************
	* LOCAL FUNCTIONS
	*****************************************/
	void RotateLocalX(float radians);
	void RotateLocalY(float radians);
	void RotateLocalZ(float radians);

	void TranslateLocal(D3DXVECTOR3 tAxis, bool bFPS = false);
	void TranslateLocalX(float scale, bool bFPS = false);
	void TranslateLocalY(float scale, bool bFPS = false);
	void TranslateLocalZ(float scale, bool bFPS = false);

	/*****************************************
	* GLOBAL FUNCTIONS
	*****************************************/
	void RotateGlobalX(float radians);
	void RotateGlobalY(float radians);
	void RotateGlobalZ(float radians);

	void TranslateGlobal(D3DXVECTOR3 tAxis);
	void TranslateGlobalX(float scale);
	void TranslateGlobalY(float scale);
	void TranslateGlobalZ(float scale);
};

#endif /*CAMERA_H_*/