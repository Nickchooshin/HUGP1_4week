#pragma once

#include "Scene.h"

class CSprite ;

class CreditScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pText ;
	CSprite *m_pBlack ;

	float m_fY, m_fYMax ;
	int m_nState ;
	float m_fTime ;
	bool m_bReturnTitle ;

public :
	static Scene* scene() ;

	CreditScene() ;
	virtual ~CreditScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;