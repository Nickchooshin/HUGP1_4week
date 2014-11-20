#pragma once

class CSprite ;
class CButton ;
class CNumberUI ;

class CBarrierButtonUI ;

class CGameObjectUI
{
private :
	int m_nSelectedType, m_nSelectedIndex ;
	bool m_bMapGrid ;
	CSprite *m_pSelectedBarrier ;
	CSprite *m_pMapGrid ;

	CSprite *m_pStageNumber ;
	CButton *m_pOperateButton ;
	CBarrierButtonUI *m_pBarrierButtonUI[4] ;

	float m_fObjectScale ;

public :
	CGameObjectUI() ;
	~CGameObjectUI() ;

	void Init() ;
	void InitScale() ;

	void SetPosition(float fX, float fY) ;

	void Update() ;

	void Render() ;
private :
	void LoadBarrierDat(int *BarrierType, int *BarrierNum) ;
	void ClearSelectedBarrier() ;
} ;