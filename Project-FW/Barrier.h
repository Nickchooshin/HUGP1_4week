#pragma once

#include "Objects.h"

typedef struct _POSITION
{
	int x, y ;

	_POSITION() : x(0), y(0) {}
} POSITION ;

class CBarrier : public CObjects
{
protected :
	POSITION *m_pBarrierArea ;
	int m_nBarrierAreaNum ;

public :
	CBarrier() ;
	virtual ~CBarrier() ;

	const POSITION* GetBarrierArea() const ;
	const int GetBarrierAreaNum() const ;
} ;