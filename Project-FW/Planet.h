#pragma once

#include "Objects.h"
#include <fmod.hpp>

class CButton ;

class CPlanet : public CObjects
{
protected :
	CSprite *m_pInfo ;
	CButton *m_pInfoButton ;

	bool m_bInfo ;
	int m_nProtectLevel ;
	POSITION m_MapIndex ;

	int m_nNowFrame ;
	float m_fAnimationTime ;

	enum State { WAIT=0, DESTROY } ;
	State m_State, m_prevState ;

	FMOD::Sound *m_pDestroy ;

public :
	CPlanet() ;
	~CPlanet() ;

	void Init() ;
	void Init(int ProtectLevel) ;

	void SetPosition(float fX, float fY) ;
	void SetMapIndex(POSITION MapIndex) ;
	void Destroy() ;
	void Deactivate() ;

	const int GetProtectLevel() const ;
	const POSITION GetMapIndex() const ;

	void Update() ;

	void Render() ;
	void Render_Info() ;
private :
	void SetInfoIndex() ;
	void Animation() ;
} ;