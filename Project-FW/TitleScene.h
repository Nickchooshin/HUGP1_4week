#pragma once

#include "Scene.h"

class CSprite ;

class TitleScene : public Scene
{
private :
	CSprite *m_pBackground ;

public :
	static Scene* scene() ;

	TitleScene() ;
	virtual ~TitleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;