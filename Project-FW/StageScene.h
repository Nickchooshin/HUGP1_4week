#pragma once

#include "Scene.h"

class CSprite ;

class StageScene : public Scene
{
private :
	CSprite *m_pBackground ;

public :
	static Scene* scene() ;

	StageScene() ;
	virtual ~StageScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;