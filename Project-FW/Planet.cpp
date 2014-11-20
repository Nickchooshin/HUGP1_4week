#include "Planet.h"
#include "Sprite.h"
#include "MapManager.h"

#include "D3dDevice.h"

CPlanet::CPlanet() : m_nProtectLevel(0),
					 m_nNowFrame(0),
					 m_fAnimationTime(0.0f),
					 m_State(WAIT), m_prevState(WAIT)
{
}
CPlanet::~CPlanet()
{
}

void CPlanet::Init()
{
	const int size = g_MapManager->GetMapSize() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init(80.0f, 140.0f, "Resource/Image/Game/Game_pln.png") ;
	m_pSprite->SetTextureUV(0.0f, 140.0f * (m_nProtectLevel-1), 80.0f, 140.0f * m_nProtectLevel) ;

	InitScale() ;
}

void CPlanet::Init(int ProtectLevel)
{
	m_nProtectLevel = ProtectLevel ;

	Init() ;
}

void CPlanet::SetMapIndex(POSITION MapIndex)
{
	m_MapIndex = MapIndex ;
}

void CPlanet::Destroy()
{
	m_State = DESTROY ;
}

const int CPlanet::GetProtectLevel() const
{
	return m_nProtectLevel ;
}

const POSITION CPlanet::GetMapIndex() const
{
	return m_MapIndex ;
}

void CPlanet::Update()
{
	Animation() ;
}

void CPlanet::Animation()
{
	int MaxFrame ;
	int Index ;

	switch(m_State)
	{
	case WAIT :
		Index = m_nProtectLevel - 1 ;
		MaxFrame = 4 ;
		break ;

	case DESTROY :
		Index = 3 ;
		MaxFrame = 1 ;
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
		top = (float)(Index * 140.0f) ;
		right = (float)(left + 80.0f) ;
		bottom = (float)(top + 140.0f) ;

		m_pSprite->SetTextureUV(left, top, right, bottom) ;

		int Frame = (int)(m_fAnimationTime / 0.1f) ;
		m_fAnimationTime -= Frame * 0.1f ;
		Frame %= MaxFrame ;
		m_nNowFrame += Frame ;
		if(m_nNowFrame>=MaxFrame)
			m_nNowFrame = 0 ;
	}

	m_prevState = m_State ;
}