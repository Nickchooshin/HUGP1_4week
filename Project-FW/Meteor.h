#pragma once

#include "Objects.h"

class CMeteor : public CObjects
{
protected :
	bool m_bMeteor ;

	int m_nNowFrame ;
	float m_fAnimationTime ;

public :
	CMeteor() ;
	~CMeteor() ;

	void Init() ;
	void InitMeteor() ;

	const bool BeMeteor() const ;

	void Update() ;
private :
	void Move() ;
	void Animation() ;
} ;