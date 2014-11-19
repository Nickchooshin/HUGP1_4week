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
	int m_nType ;

	int m_nNowFrame ;
	float m_fAnimationTime ;

	enum State { BUILD=0, WAIT } ;
	State m_State, m_prevState ;

public :
	CBarrier() ;
	~CBarrier() ;

	void Init() ;
	void Init(int Type) ;

	const POSITION* GetBarrierArea() const ;
	const int GetBarrierAreaNum() const ;

	void Update() ;
private :
	void Animation() ;
} ;