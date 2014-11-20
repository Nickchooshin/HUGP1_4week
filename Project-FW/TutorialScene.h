#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;

class TutorialScene : public Scene
{
private :
	int m_nSceneNum ;
	CSprite *m_pTutorial[7] ;

public :
	static Scene* scene() ;

	TutorialScene() ;
	virtual ~TutorialScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;