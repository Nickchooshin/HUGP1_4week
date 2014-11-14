#include "LineEffect.h"
#include "Sprite.h"

#include "D3dDevice.h"

CLineEffect::CLineEffect() : m_Direction(NONE),
							 m_fSpeed(0.0f),
							 m_bLife(false)
{
}
CLineEffect::~CLineEffect()
{
}

void CLineEffect::Init()
{
	int WinWidth = g_D3dDevice->GetWinWidth() ;
	int WinHeight = g_D3dDevice->GetWinHeight() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Image/Title/Line.png") ;
	m_pSprite->SetAlpha(127) ;

	m_Direction = (DIRECTION)(rand() % 4 + 1) ;
	m_fSpeed = (rand()%5+1) * 4.0f + 8.0f ;

	switch(m_Direction)
	{
	case UP :
		m_fX = rand() % WinWidth ;
		m_fY = -50.0f ;
		break ;

	case DOWN :
		m_fX = rand() % WinWidth ;
		m_fY = (float)WinHeight + 50.0f ;
		break ;

	case RIGHT :
		m_fX = -50.0f ;
		m_fY = rand() % WinHeight ;
		break ;

	case LEFT :
		m_fX = (float)WinWidth + 50.0f ;
		m_fY = rand() % WinHeight ;
		break ;
	}

	if(m_Direction==DOWN || m_Direction==LEFT)
		m_fSpeed = -m_fSpeed ;

	if(m_Direction==UP || m_Direction==DOWN)
		m_pSprite->SetAngle(90.0f) ;

	m_bLife = true ;
}

void CLineEffect::Update()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;
	float fSpeed = m_fSpeed * g_D3dDevice->GetMoveTime() ;

	switch(m_Direction)
	{
	case UP :
	case DOWN :
		m_fY += fSpeed ;
		break ;

	case RIGHT :
	case LEFT :
		m_fX += fSpeed ;
		break ;
	}

	if( (m_fX < -50.0f) || (m_fX > WinWidth + 50.0f) ||
		(m_fY < -50.0f) || (m_fY > WinHeight + 50.0f) )
		m_bLife = false ;
}

const bool CLineEffect::IsLife() const
{
	return m_bLife ;
}