#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CButton ;

class TitleScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pTitle ;
	CButton *m_pStartButton, *m_pExitButton ;

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	TitleScene() ;
	virtual ~TitleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;