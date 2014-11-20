#pragma once

typedef struct _POSITION
{
	int x, y ;

	_POSITION() : x(0), y(0) {}
	_POSITION(int X, int Y) : x(X), y(Y) {}
} POSITION ;

class CSprite ;

class CObjects
{
protected :
	float m_fX, m_fY ;
	float m_fScale ;
	CSprite *m_pSprite ;

public :
	CObjects() ;
	virtual ~CObjects() ;

	virtual void Init() = 0 ;
	void InitScale() ;

	virtual void SetPosition(float fX, float fY) ;

	const float GetPositionX() const ;
	const float GetPositionY() const ;

	virtual void Update() ;

	virtual void Render() ;
} ;