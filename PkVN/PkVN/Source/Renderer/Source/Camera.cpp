#include "../Header/Camera.h"

Camera::Camera()
{
	D3DXMatrixIdentity(&m_tViewMatrix);
	D3DXMatrixIdentity(&m_tProjMatrix);
}

Camera::~Camera()
{

}

D3DXMATRIX Camera::GetViewMatrix(bool bTranslate)
{
	D3DXMATRIX rotationMat(m_tViewMatrix), transformMat;
	rotationMat._41 = rotationMat._42 = rotationMat._43 = 0.0f;
	D3DXMatrixTranspose(&rotationMat, &rotationMat);

	D3DXMatrixIdentity(&transformMat);
	transformMat._41 = -m_tViewMatrix._41;
	transformMat._42 = -m_tViewMatrix._42;
	transformMat._43 = -m_tViewMatrix._43;

	D3DXMatrixMultiply(&transformMat, &transformMat, &rotationMat);

	if (bTranslate)
		return transformMat;
	else
		return rotationMat;
}

void Camera::BuildProjectionMatrix(float fFoV, float fAspectRatio, float fNearPlane, float fFarPlane)
{
	D3DXMatrixPerspectiveFovLH(&m_tProjMatrix, fFoV, fAspectRatio, fNearPlane, fFarPlane);
}

D3DXVECTOR3 Camera::GetViewXAxis()
{
	D3DXVECTOR3 xAxis;
	xAxis.x = m_tViewMatrix._11;
	xAxis.y = m_tViewMatrix._12;
	xAxis.z = m_tViewMatrix._13;

	return xAxis;
}

D3DXVECTOR3 Camera::GetViewYAxis()
{
	D3DXVECTOR3 yAxis;
	yAxis.x = m_tViewMatrix._21;
	yAxis.y = m_tViewMatrix._22;
	yAxis.z = m_tViewMatrix._23;

	return yAxis;
}

D3DXVECTOR3 Camera::GetViewZAxis()
{
	D3DXVECTOR3 zAxis;
	zAxis.x = m_tViewMatrix._31;
	zAxis.y = m_tViewMatrix._32;
	zAxis.z = m_tViewMatrix._33;

	return zAxis;
}

D3DXVECTOR3 Camera::GetViewPos()
{
	D3DXVECTOR3 pos;
	pos.x = m_tViewMatrix._41;
	pos.y = m_tViewMatrix._42;
	pos.z = m_tViewMatrix._43;

	return pos;
}

void Camera::SetViewXAxis(float x, float y, float z)
{
	m_tViewMatrix._11 = x;
	m_tViewMatrix._12 = y;
	m_tViewMatrix._13 = z;
}

void Camera::SetViewXAxis(D3DXVECTOR3 tVec)
{
	m_tViewMatrix._11 = tVec.x;
	m_tViewMatrix._12 = tVec.y;
	m_tViewMatrix._13 = tVec.z;
}

void Camera::SetViewYAxis(float x, float y, float z)
{
	m_tViewMatrix._21 = x;
	m_tViewMatrix._22 = y;
	m_tViewMatrix._23 = z;
}

void Camera::SetViewYAxis(D3DXVECTOR3 tVec)
{
	m_tViewMatrix._21 = tVec.x;
	m_tViewMatrix._22 = tVec.y;
	m_tViewMatrix._23 = tVec.z;
}

void Camera::SetViewZAxis(float x, float y, float z)
{
	m_tViewMatrix._31 = x;
	m_tViewMatrix._32 = y;
	m_tViewMatrix._33 = z;
}

void Camera::SetViewZAxis(D3DXVECTOR3 tVec)
{
	m_tViewMatrix._31 = tVec.x;
	m_tViewMatrix._32 = tVec.y;
	m_tViewMatrix._33 = tVec.z;
}

void Camera::SetViewPos(float x, float y, float z)
{
	m_tViewMatrix._41 = x;
	m_tViewMatrix._42 = y;
	m_tViewMatrix._43 = z;
}

void Camera::SetViewPos(D3DXVECTOR3 tVec)
{
	m_tViewMatrix._41 = tVec.x;
	m_tViewMatrix._42 = tVec.y;
	m_tViewMatrix._43 = tVec.z;
}

/*****************************************
* LOCAL FUNCTIONS
*****************************************/
void Camera::RotateLocalX(float radians)
{
	D3DXMATRIX rotationMat;
	D3DXVECTOR3 localX(m_tViewMatrix._11, m_tViewMatrix._12, m_tViewMatrix._13);
	D3DXMatrixRotationAxis(&rotationMat, &localX, radians);

	D3DXVECTOR4 pos(m_tViewMatrix._41, m_tViewMatrix._42, m_tViewMatrix._43, m_tViewMatrix._44);

	m_tViewMatrix._41 = m_tViewMatrix._42 = m_tViewMatrix._43 = 0.0f;

	D3DXMatrixMultiply(&m_tViewMatrix, &m_tViewMatrix, &rotationMat);
	m_tViewMatrix._41 = pos.x; m_tViewMatrix._42 = pos.y;
	m_tViewMatrix._43 = pos.z; m_tViewMatrix._44 = pos.w;
}

void Camera::RotateLocalY(float radians)
{
	D3DXMATRIX rotationMat;
	D3DXVECTOR3 localY(m_tViewMatrix._21, m_tViewMatrix._22, m_tViewMatrix._23);
	D3DXMatrixRotationAxis(&rotationMat, &localY, radians);

	D3DXVECTOR4 pos(m_tViewMatrix._41, m_tViewMatrix._42, m_tViewMatrix._43, m_tViewMatrix._44);

	m_tViewMatrix._41 = m_tViewMatrix._42 = m_tViewMatrix._43 = 0.0f;

	D3DXMatrixMultiply(&m_tViewMatrix, &m_tViewMatrix, &rotationMat);
	m_tViewMatrix._41 = pos.x; m_tViewMatrix._42 = pos.y;
	m_tViewMatrix._43 = pos.z; m_tViewMatrix._44 = pos.w;
}

void Camera::RotateLocalZ(float radians)
{
	D3DXMATRIX rotationMat;
	D3DXVECTOR3 localZ(m_tViewMatrix._31, m_tViewMatrix._32, m_tViewMatrix._33);
	D3DXMatrixRotationAxis(&rotationMat, &localZ, radians);

	D3DXVECTOR4 pos(m_tViewMatrix._41, m_tViewMatrix._42, m_tViewMatrix._43, m_tViewMatrix._44);

	m_tViewMatrix._41 = m_tViewMatrix._42 = m_tViewMatrix._43 = 0.0f;

	D3DXMatrixMultiply(&m_tViewMatrix, &m_tViewMatrix, &rotationMat);
	m_tViewMatrix._41 = pos.x; m_tViewMatrix._42 = pos.y;
	m_tViewMatrix._43 = pos.z; m_tViewMatrix._44 = pos.w;
}

void Camera::TranslateLocal(D3DXVECTOR3 tAxis, bool bFPS)
{
	if (bFPS)
	{
		TranslateLocalX(tAxis.x, bFPS);
		TranslateLocalY(tAxis.y, bFPS);
		TranslateLocalZ(tAxis.z, bFPS);
		return;
	}

	TranslateLocalX(tAxis.x);
	TranslateLocalY(tAxis.y);
	TranslateLocalZ(tAxis.z);
}

void Camera::TranslateLocalX(float scale, bool bFPS)
{
	m_tViewMatrix._41 += m_tViewMatrix._11 * scale;
	m_tViewMatrix._42 += m_tViewMatrix._12 * scale;
	m_tViewMatrix._43 += m_tViewMatrix._13 * scale;
}

void Camera::TranslateLocalY(float scale, bool bFPS)
{
	m_tViewMatrix._41 += m_tViewMatrix._21 * scale;
	m_tViewMatrix._42 += m_tViewMatrix._22 * scale;
	m_tViewMatrix._43 += m_tViewMatrix._23 * scale;
}

void Camera::TranslateLocalZ(float scale, bool bFPS)
{
	m_tViewMatrix._41 += m_tViewMatrix._31 * scale;
	m_tViewMatrix._42 += m_tViewMatrix._32 * scale;
	m_tViewMatrix._43 += m_tViewMatrix._33 * scale;
}

/*****************************************
* GLOBAL FUNCTIONS
*****************************************/
void Camera::RotateGlobalX(float radians)
{
	D3DXMATRIX rotationMat;
	D3DXVECTOR4 pos(m_tViewMatrix._41, m_tViewMatrix._42, m_tViewMatrix._43, m_tViewMatrix._44);
	D3DXMatrixRotationX(&rotationMat, radians);

	m_tViewMatrix._41 = m_tViewMatrix._42 = m_tViewMatrix._43 = 0.0f;

	D3DXMatrixMultiply(&m_tViewMatrix, &m_tViewMatrix, &rotationMat);
	m_tViewMatrix._41 = pos.x; m_tViewMatrix._42 = pos.y;
	m_tViewMatrix._43 = pos.z; m_tViewMatrix._44 = pos.w;
}

void Camera::RotateGlobalY(float radians)
{
	D3DXMATRIX rotationMat;
	D3DXVECTOR4 pos(m_tViewMatrix._41, m_tViewMatrix._42, m_tViewMatrix._43, m_tViewMatrix._44);
	D3DXMatrixRotationY(&rotationMat, radians);

	m_tViewMatrix._41 = m_tViewMatrix._42 = m_tViewMatrix._43 = 0.0f;

	D3DXMatrixMultiply(&m_tViewMatrix, &m_tViewMatrix, &rotationMat);
	m_tViewMatrix._41 = pos.x; m_tViewMatrix._42 = pos.y;
	m_tViewMatrix._43 = pos.z; m_tViewMatrix._44 = pos.w;
}

void Camera::RotateGlobalZ(float radians)
{
	D3DXMATRIX rotationMat;
	D3DXVECTOR4 pos(m_tViewMatrix._41, m_tViewMatrix._42, m_tViewMatrix._43, m_tViewMatrix._44);
	D3DXMatrixRotationZ(&rotationMat, radians);

	m_tViewMatrix._41 = m_tViewMatrix._42 = m_tViewMatrix._43 = 0.0f;

	D3DXMatrixMultiply(&m_tViewMatrix, &m_tViewMatrix, &rotationMat);
	m_tViewMatrix._41 = pos.x; m_tViewMatrix._42 = pos.y;
	m_tViewMatrix._43 = pos.z; m_tViewMatrix._44 = pos.w;
}

void Camera::TranslateGlobal(D3DXVECTOR3 tAxis)
{
	m_tViewMatrix._41 += tAxis.x;
	m_tViewMatrix._42 += tAxis.y;
	m_tViewMatrix._43 += tAxis.z;
}

void Camera::TranslateGlobalX(float scale)
{
	m_tViewMatrix._41 += scale;
}

void Camera::TranslateGlobalY(float scale)
{
	m_tViewMatrix._42 += scale;
}

void Camera::TranslateGlobalZ(float scale)
{
	m_tViewMatrix._43 += scale;
}


