#pragma once

#include <fmod.hpp>

class CSprite ;

class CStageStartUI
{
private :
	CSprite *m_pBlack ;
	CSprite *m_pStageStart ;

	int m_nState ;
	float m_fTime ;
	bool m_bStageStartEnd ;

	FMOD::Sound *m_pEStageStart ;

public :
	CStageStartUI() ;
	~CStageStartUI() ;

	void Init() ;

	const bool BeStageStartEnd() const ;

	void Update() ;

	void Render() ;
} ;