#pragma once

#include "Objects.h"

class CPlanet : public CObjects
{
protected :
	int m_nProtectLevel ;

public :
	CPlanet() ;
	~CPlanet() ;

	void Init() ;
	void Init(int ProtectLevel) ;
} ;