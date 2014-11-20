#include "Meteor.h"
#include "Sprite.h"

#include "D3dDevice.h"

CMeteor::CMeteor() : m_bMeteor(true),
					 m_nNowFrame(0),
					 m_fAnimationTime(0.0f)
{
}
CMeteor::~CMeteor()
{
}

void CMeteor::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init(430.0f, 360.0f, "Resource/Image/Game/Game_opr_meteor.png") ;
	m_pSprite->SetTextureUV(0.0f, 0.0f, 430.0f, 360.0f) ;
}

void CMeteor::InitMeteor()
{
	SetPosition(g_D3dDevice->GetWinWidth() + 430.0f, g_D3dDevice->GetWinHeight() + 360.0f) ;
	m_bMeteor = true ;
}

const bool CMeteor::BeMeteor() const
{
	return m_bMeteor ;
}

void CMeteor::Update()
{
	Move() ;

	Animation() ;
}

void CMeteor::Move()
{
	if(!m_bMeteor)
		return ;

	float fSpeed = g_D3dDevice->GetMoveTime() * 10.0f ;

	m_fX -= fSpeed ;
	m_fY -= fSpeed ;

	if(m_fX < -(430.0f/2.0f) && m_fY < -(360.0f/2.0f))
		m_bMeteor = false ;
}

void CMeteor::Animation()
{
	int MaxFrame = 2 ;

	m_fAnimationTime += g_D3dDevice->GetTime() ;

	if(m_fAnimationTime>=0.1f)
	{
		float left, top, right, bottom ;
		left = (float)(m_nNowFrame * 430.0f) ;
		top = 0.0f ;
		right = (float)(left + 430.0f) ;
		bottom = 360.0f ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;

		int Frame = (int)(m_fAnimationTime / 0.1f) ;
		m_fAnimationTime -= Frame * 0.1f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
			m_nNowFrame = 0 ;
	}
}