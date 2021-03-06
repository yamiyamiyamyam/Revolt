#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void Setup(D3DXVECTOR3*	pvTarget);
	void Update();
	void WndProc(HWND hWnd, UINT message,
		WPARAM wParam, LPARAM lParam);

	void SetLookAt(D3DXVECTOR3* pvLookAt) { m_vNextLootAt = *pvLookAt; }

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;
	D3DXVECTOR3		m_vNextLootAt;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	float			m_fCamTime;
	D3DXVECTOR3		m_vCamRotAngle;
};

