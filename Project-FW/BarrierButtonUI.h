#pragma once

class CSprite ;
class CButton ;
class CNumberUI ;

class CBarrierButtonUI
{
private :
	int m_nType, m_nNum ;
	bool m_bPuton ;

	CButton *m_pButton ;
	CSprite *m_pInfo ;
	CSprite *m_pSelectedSprite ;
	CNumberUI *m_pNumberUI ;

public :
	CBarrierButtonUI() ;
	~CBarrierButtonUI() ;

	void Init(int Type, int Num) ;

	void SetPosition(float fX, float fY) ;
	void SetActivate(bool bActivate) ;
	void SubBarrierNum() ;
	
	const int GetType() const ;
	CSprite* GetSelectedSprite() const ;
	const bool BeClick() const ;

	void Update() ;

	void Render() ;
} ;