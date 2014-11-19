#include "Barrier.h"
#include "Sprite.h"

#include "D3dDevice.h"

CBarrier::CBarrier() : m_pBarrierArea(0),
					   m_nBarrierAreaNum(NULL),
					   m_nType(0),
					   m_nNowFrame(0),
					   m_fAnimationTime(0.0f),
					   m_State(BUILD), m_prevState(BUILD)
{
}
CBarrier::~CBarrier()
{
	if(m_pBarrierArea!=NULL)
		delete m_pBarrierArea ;
}

void CBarrier::Init()
{
	m_pSprite = new CSprite() ;
	m_pSprite->Init(80.0f, 123.0f, "Resource/Image/Game/Game_bar.png") ;
	m_pSprite->SetTextureUV(0.0f, 123.0f * 5.0f, 80.0f, 123.0f * 6.0f) ;
}

void CBarrier::Init(int Type)
{
	int i ;

	m_nType = Type ;

	if(m_nType==1)
	{
		m_nBarrierAreaNum = 5 ;
		m_pBarrierArea = new POSITION[5] ;

		for(i=0; i<5; i++)
		{
			m_pBarrierArea[i].x = -2 + i ;
			m_pBarrierArea[i].y = 0 ;
		}
	}
	else if(m_nType==2)
	{
		m_nBarrierAreaNum = 5 ;
		m_pBarrierArea = new POSITION[5] ;

		for(i=0; i<5; i++)
		{
			m_pBarrierArea[i].x = 0 ;
			m_pBarrierArea[i].y = -2 + i ;
		}
	}
	else if(m_nType==3)
	{
		m_nBarrierAreaNum = 5 ;
		m_pBarrierArea = new POSITION[5] ;

		m_pBarrierArea[0].x = 0 ;
		m_pBarrierArea[0].y = -1 ;
		m_pBarrierArea[1].x = -1 ;
		m_pBarrierArea[1].y = 0 ;
		m_pBarrierArea[2].x = 0 ;
		m_pBarrierArea[2].y = 0 ;
		m_pBarrierArea[3].x = 1 ;
		m_pBarrierArea[3].y = 0 ;
		m_pBarrierArea[4].x = 0 ;
		m_pBarrierArea[4].y = 1 ;
	}
	else if(m_nType==4)
	{
		m_nBarrierAreaNum = 9 ;
		m_pBarrierArea = new POSITION[9] ;

		for(i=0; i<9; i++)
		{
			m_pBarrierArea[i].x = i % 3 -1 ;
			m_pBarrierArea[i].y = i / 3 ;
		}
	}
	else if(m_nType==5)
	{
		m_nBarrierAreaNum = 9 ;
		m_pBarrierArea = new POSITION[9] ;

		m_pBarrierArea[0].x = -2 ;
		m_pBarrierArea[0].y = -2 ;
		m_pBarrierArea[1].x = 2 ;
		m_pBarrierArea[1].y = -2 ;
		m_pBarrierArea[2].x = -1 ;
		m_pBarrierArea[2].y = -1 ;
		m_pBarrierArea[3].x = 1 ;
		m_pBarrierArea[3].y = -1 ;
		m_pBarrierArea[4].x = 0 ;
		m_pBarrierArea[4].y = 0 ;
		m_pBarrierArea[5].x = -1 ;
		m_pBarrierArea[5].y = 1 ;
		m_pBarrierArea[6].x = 1 ;
		m_pBarrierArea[6].y = 1 ;
		m_pBarrierArea[7].x = -2 ;
		m_pBarrierArea[7].y = 2 ;
		m_pBarrierArea[8].x = 2 ;
		m_pBarrierArea[8].y = 2 ;
	}

	Init() ;
}

const POSITION* CBarrier::GetBarrierArea() const
{
	return m_pBarrierArea ;
}

const int CBarrier::GetBarrierAreaNum() const
{
	return m_nBarrierAreaNum ;
}

void CBarrier::Update()
{
	Animation() ;
}

void CBarrier::Animation()
{
	const int MaxFrame = 6 ;
	int Index ;

	switch(m_State)
	{
	case BUILD :
		Index = 5 ;
		break ;

	case WAIT :
		Index = m_nType-1 ;
		break ;
	}

	m_fAnimationTime += g_D3dDevice->GetTime() ;

	if(m_fAnimationTime>=0.1f || (m_State!=m_prevState))
	{
		if(m_State!=m_prevState)
		{
			m_nNowFrame = 0 ;
			m_fAnimationTime = 0.0f ;
		}

		float left, top, right, bottom ;
		left = (float)(m_nNowFrame * 80.0f) ;
		top = (float)(Index * 123.0f) ;
		right = (float)(left + 80.0f) ;
		bottom = (float)(top + 123.0f) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;

		int Frame = (int)(m_fAnimationTime / 0.1f) ;
		m_fAnimationTime -= Frame * 0.1f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
		{
			m_nNowFrame = 0 ;
			m_State = WAIT ;
		}
	}

	m_prevState = m_State ;
}