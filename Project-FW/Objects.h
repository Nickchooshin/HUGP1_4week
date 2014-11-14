#pragma once

class CSprite ;

class CObjects
{
protected :
	float m_fX, m_fY ;
	CSprite *m_pSprite ;

public :
	CObjects() ;
	virtual ~CObjects() ;

	virtual void Init() = 0 ;

	virtual void SetPosition(float fX, float fY) ;

	const float GetPositionX() const ;
	const float GetPositionY() const ;

	virtual void Update() ;

	virtual void Render() ;
} ;