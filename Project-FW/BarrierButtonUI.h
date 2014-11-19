#pragma once

class CSprite ;
class CButton ;
class CNumberUI ;

class CBarrierButtonUI
{
private :
	int m_nNum ;
	bool m_bPuton ;

	CButton *m_pButton ;
	CSprite *m_pInfo ;
	CNumberUI *m_pNumberUI ;

public :
	CBarrierButtonUI() ;
	~CBarrierButtonUI() ;

	void Init(int Type, int Num) ;

	void SetPosition(float fX, float fY) ;

	void Update() ;

	void Render() ;
} ;