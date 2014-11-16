#pragma once

#include "Objects.h"

class CLineEffect : public CObjects
{
private :
	enum DIRECTION { NONE=0, UP, DOWN, RIGHT, LEFT} ;
	DIRECTION m_Direction ;
	float m_fSpeed, m_fScale ;
	float m_fTexSizeHalf ;
	bool m_bLife ;

public :
	CLineEffect() ;
	virtual ~CLineEffect() ;

	void Init() ;

	void Update() ;

	const bool IsLife() const ;
} ;