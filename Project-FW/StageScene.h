#pragma once

#include "Scene.h"

class CSprite ;
class CButton ;

class StageScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CButton *m_pNextButton, *m_pPrevButton ;
	CSprite *m_pStageNumber[20] ;
	CButton *m_pStageButton[20] ;
	CSprite *m_pStageSelect ;

public :
	static Scene* scene() ;

	StageScene() ;
	virtual ~StageScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;