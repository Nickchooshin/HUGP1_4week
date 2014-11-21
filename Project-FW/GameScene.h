#pragma once

#include "Scene.h"
#include <fmod.hpp>

class CSprite ;
class CGameObjectUI ;
class CStageStartUI ;

class GameScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CGameObjectUI *m_pGameObjectUI ;
	CStageStartUI *m_pStageStartUI ;

	FMOD::Sound *m_pBGM ;

public :
	static Scene* scene() ;

	GameScene() ;
	virtual ~GameScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;