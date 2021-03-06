#include "stdafx.h"
#include "c321GO.h"
#include "Object.h"
#include "RacingScene.h"

c321GO::c321GO()
{
}

c321GO::~c321GO()
{
}

void c321GO::Setup()
{
	Object* gogo = new Object;
	gogo->SetMeshData(new cMesh);
	gogo->GetMeshData()->LoadMesh("Objects/gogo", "gogo.obj");
	m_vec321go.push_back(gogo);

	Object* go1 = new Object;
	go1->SetMeshData(new cMesh);
	go1->GetMeshData()->LoadMesh("Objects/go1", "go1.obj");
	m_vec321go.push_back(go1);

	Object* go2 = new Object;
	go2->SetMeshData(new cMesh);
	go2->GetMeshData()->LoadMesh("Objects/go2", "go2.obj");
	m_vec321go.push_back(go2);

	Object* go3 = new Object;
	go3->SetMeshData(new cMesh);
	go3->GetMeshData()->LoadMesh("Objects/go3", "go3.obj");
	m_vec321go.push_back(go3);

	m_fAngle = D3DX_PI;
	m_nCount = 3;
	m_fTime = 0.0f;
	m_isStart = false;
	m_fAngleRatio = 0.f;
	m_isRender = false;
}

void c321GO::Update()
{
	//매쉬 방향은 Y가 PI일때 정면

	Count();
}

void c321GO::Render()
{
	if (m_isRender)
	{
		m_vec321go[m_nCount]->Render();
	}
}

void c321GO::Destroy()
{
	for each(Object* p in m_vec321go)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	m_vec321go.clear();
}

void c321GO::StartCount()
{
	m_isStart = true;
	m_isRender = true;
	m_fAngle = D3DX_PI;
	m_nCount = 3;
	m_fTime = 0.0f;
	
	posStart = *g_pCamManager->GetCamPos();
	posStart.y += 1;
	posEnd = posStart;
}

void c321GO::Count()
{
	D3DXVECTOR3 camPos = *g_pCamManager->GetCamPos();
	D3DXVECTOR3 camLook = *g_pCamManager->GetLookAt();
	camLook.y += 1;

	float distToCam = 1.5f;
	float size = 0.5f;
	float Lerp = 0.1;

	D3DXVECTOR3 direc = camPos - camLook; // 안쪽으로의 방향
	D3DXVec3Normalize(&direc, &direc); 
	D3DXVECTOR3 pos = camPos - (direc * distToCam); // 매쉬 위치할 곳

	if (m_isStart)
	{
		if (m_fTime == 0)
		{
			if (m_nCount != 0)
			{
				g_pSoundManager->Play("countdown.wav", 0.6f);
			}
			else
			{
				g_pSoundManager->Play("countdown_0.wav", 0.6f);
				g_pSoundManager->Play("countdown_1.wav", 0.6f);
			}
			
		}

		m_fTime += g_pTimeManager->GetElapsedTime();

		float min = -1;

		if (m_fTime > 0.875)
		{
			if (m_nCount != 0)
			{
				m_fAngle = (((m_fTime * 4) + (0.5f * min)) * D3DX_PI);
			}
		}
		else if (m_fTime > 0.125)
		{
			m_fAngle = D3DX_PI;

			if (m_nCount % 2 == 0)
			{
				min = 1;
			}
			else
			{
				min = -1;
			}
		}
		else
		{
			m_fAngle = (((m_fTime * 4) - (0.5f * min)) * D3DX_PI);
		}

		if (m_fTime > 1)
		{
			if (m_nCount == 0)
			{
				m_isStart = false;
				m_pRacingScene->SetRaceProg(RACE_PROG_GO);
			}
			else
			{
				m_nCount--;
			}
			
			m_fTime = 0;

		}
	}

	D3DXMATRIXA16 mat, matR, matRY;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matRY);

	D3DXMatrixRotationY(&matRY, m_fAngle);
	matR = matRY;

	mat = matR;

	D3DXVec3TransformNormal(&direc, &direc, &mat);

	if (m_isStart)
	{
		D3DXVec3Lerp(&posStart, &posStart, &pos, Lerp);
	}
	else
	{
		D3DXVec3Lerp(&posStart, &posStart, &posEnd, Lerp);
		D3DXVECTOR3 dist = posEnd - posStart;
		float distance = D3DXVec3Length(&dist);
		if (distance < 0.3)
		{
			m_isRender = false;
		}
	}

	m_vec321go[m_nCount]->SetPosition(posStart);
	m_vec321go[m_nCount]->SetQuaternion(direc);
	m_vec321go[m_nCount]->SetSize({ size, size, size });
}
