#pragma once

class CSprite ;
class CButton ;
class CNumberUI ;

class CGameObjectUI
{
private :
	CSprite *m_pStageNumber ;
	CButton *m_pOperateButton ;
	CButton *m_pBarrierButton[5] ;
	CNumberUI *m_pBarrierNum[5] ;

public :
	CGameObjectUI() ;
	~CGameObjectUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;

	void Update() ;

	void Render() ;
} ;