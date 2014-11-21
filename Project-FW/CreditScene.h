#pragma once

#include "Scene.h"
#include <fmod.hpp>

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

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	CreditScene() ;
	virtual ~CreditScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;