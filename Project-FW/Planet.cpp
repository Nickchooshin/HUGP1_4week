#include "Planet.h"
#include "Sprite.h"
#include "MapManager.h"

CPlanet::CPlanet() : m_nProtectLevel(0)
{
}
CPlanet::~CPlanet()
{
}

void CPlanet::Init()
{
	char filepath[100] ;
	const int size = g_MapManager->GetMapSize() ;
	wsprintf(filepath, "Resource/Image/Game/%dx%d/game_pln_%dx%d_%d.png", size, size, size, size, m_nProtectLevel) ;

	m_pSprite = new CSprite ;
	m_pSprite->Init(filepath) ;
}

void CPlanet::Init(int ProtectLevel)
{
	m_nProtectLevel = ProtectLevel ;

	Init() ;
}