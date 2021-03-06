#pragma once

#define g_pDeviceManager DeviceManager::GetInstance()
#define g_pD3DDevice	DeviceManager::GetInstance()->GetDevice()
#define MgrD3DDevice g_pD3DDevice
class DeviceManager
{
public:
	SINGLETONE(DeviceManager);
private:
	LPDIRECT3D9		m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	LPDIRECT3DDEVICE9	m_pD3DDevice2;

public:
	LPDIRECT3DDEVICE9	GetDevice();
	void Destroy();
};

