#pragma once

class CSprite ;
class CButton ;
class CNumberUI ;

class CBarrierButtonUI ;

class CGameObjectUI
{
private :
	int m_nBarrierType[4], m_nBarrierNum[4] ;

	CSprite *m_pStageNumber ;
	CButton *m_pOperateButton ;
	CBarrierButtonUI *m_pBarrierButtonUI[4] ;

public :
	CGameObjectUI() ;
	~CGameObjectUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;

	void Update() ;

	void Render() ;
private :
	void LoadBarrierDat() ;
} ;