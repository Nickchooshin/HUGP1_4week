#pragma once

#include "Scene.h"

class CSprite ;
class CGameObjectUI ;

class GameScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CGameObjectUI *m_pGameObjectUI ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;