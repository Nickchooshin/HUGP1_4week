#pragma once

class CSprite ;
class CButton ;

class CResultUI
{
private :
	int m_nResult ;
	CSprite *m_pBackground ;
	CSprite *m_pResult ;
	CButton *m_pFinishButton, *m_pNextStageButton, *m_pRetryButton, *m_pStageSelectButton ;

	float m_fTime ;
	int m_nState ;

public :
	CResultUI() ;
	~CResultUI() ;

	void Init() ;
	void InitValue() ;

	void SetResult(int Result) ;

	void Update() ;

	void Render() ;
} ;