#pragma once

#include "Objects.h"

class CSprite ;

class CBarrier : public CObjects
{
protected :
	CSprite *m_pActivate ;
	POSITION *m_pBarrierArea ;
	int m_nBarrierAreaNum ;
	int m_nType ;
	bool m_bActivate ;

	int m_nNowFrame, m_nNowFrame_A ;
	float m_fAnimationTime, m_fAnimationTime_A ;

	enum State { BUILD=0, WAIT } ;
	State m_State, m_prevState ;

public :
	CBarrier() ;
	~CBarrier() ;

	void Init() ;
	void Init(int Type) ;

	void Activate() ;

	const POSITION* GetBarrierArea() const ;
	const int GetBarrierAreaNum() const ;

	void Update() ;

	void Render() ;
private :
	void Animation() ;
	void Animation_Activate() ;
} ;