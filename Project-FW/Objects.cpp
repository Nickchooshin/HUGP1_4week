#include "Objects.h"
#include "Sprite.h"

#include "MapManager.h"

CObjects::CObjects() : m_fX(0.0f), m_fY(0.0f),
					   m_fScale(1.0f),
					   m_pSprite(NULL)
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CObjects::InitScale()
{
	switch(g_MapManager->GetMapSize())
	{
	case 3 :
		m_fScale = 1.0f ;
		break ;

	case 6 :
		m_fScale = 0.5f ;
		break ;

	case 9 :
		m_fScale = 0.3375f ;
		break ;
	}
}

void CObjects::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

const float CObjects::GetPositionX() const
{
	return m_fX ;
}

const float CObjects::GetPositionY() const
{
	return m_fY ;
}

void CObjects::Update()
{
}

void CObjects::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->SetScale(m_fScale, m_fScale) ;
	m_pSprite->Render() ;
}