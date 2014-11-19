#pragma once

#include "Objects.h"

class CPlanet : public CObjects
{
protected :
	int m_nProtectLevel ;

	int m_nNowFrame ;
	float m_fAnimationTime ;

	enum State { WAIT=0, DESTROY } ;
	State m_State, m_prevState ;

public :
	CPlanet() ;
	~CPlanet() ;

	void Init() ;
	void Init(int ProtectLevel) ;

	void Update() ;
private :
	void Animation() ;
} ;