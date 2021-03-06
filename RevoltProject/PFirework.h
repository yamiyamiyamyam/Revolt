#pragma once

#include "PSystem.h"

//===================================================================
// - written by 정종훈
// - 불꽃놀이 파티클 이펙트
//===================================================================


class PFirework : public PSystem
{
public:
	// 시스템이 가진 파티클의 수, 각 파티클 크기
	PFirework(int numParticles, float size);

	virtual void SetPosition(D3DXVECTOR3* origin) { _origin = *origin; }
	virtual void ResetParticle(ST_Attribute* attribute);
	virtual void Update(float timeDelta);
	virtual void PreRender();
	virtual void PostRender();
};

