#include "Planet.h"
#include "Sprite.h"
#include "Button.h"
#include "MapManager.h"

#include "D3dDevice.h"
#include "ButtonManager.h"
#include "MusicManager.h"

CPlanet::CPlanet() : m_pInfo(NULL),
					 m_pInfoButton(NULL),
					 m_bInfo(false),
					 m_nProtectLevel(0),
					 m_nNowFrame(0),
					 m_fAnimationTime(0.0f),
					 m_State(WAIT), m_prevState(WAIT),
					 m_pDestroy(NULL)
{
}
CPlanet::~CPlanet()
{
	if(m_pInfo!=NULL)
		delete m_pInfo ;
	if(m_pInfoButton!=NULL)
		g_ButtonManager->DeleteButton(m_pInfoButton) ;
}

void CPlanet::Init()
{
	const int size = g_MapManager->GetMapSize() ;

	m_pSprite = new CSprite ;
	m_pSprite->Init(80.0f, 140.0f, "Resource/Image/Game/Game_pln.png") ;
	m_pSprite->SetTextureUV(0.0f, 140.0f * (m_nProtectLevel-1), 80.0f, 140.0f * m_nProtectLevel) ;

	m_pInfo = new CSprite ;
	m_pInfo->Init(100.0f, 60.0f, "Resource/Image/Game/Game_pln_info.png") ;
	m_pInfo->SetTextureUV(0.0f, 0.0f, 100.0f, 60.0f) ;

	m_pInfoButton = new CButton ;
	m_pInfoButton->Init(80.0f * m_fScale, 140.0f * m_fScale, "Resource/Image/Black.png") ;
	m_pInfoButton->SetIndex(0, 1, 0, 0) ;
	m_pInfoButton->SetPutonActivate(true) ;
	m_pInfoButton->SetPutonSound("Resource/Sound/SE_click.mp3") ;
	g_ButtonManager->AddButton(m_pInfoButton) ;

	m_pDestroy = g_MusicManager->LoadMusic("Resource/Sound/SE_destroy.mp3", false, false) ;

	InitScale() ;
}

void CPlanet::Init(int ProtectLevel)
{
	m_nProtectLevel = ProtectLevel ;

	Init() ;
}

void CPlanet::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;

	m_pInfoButton->SetPosition(m_fX, m_fY) ;
}

void CPlanet::SetMapIndex(POSITION MapIndex)
{
	m_MapIndex = MapIndex ;
}

void CPlanet::Destroy()
{
	m_State = DESTROY ;

	g_MusicManager->PlayMusic(m_pDestroy, 1) ;
}

void CPlanet::Deactivate()
{
	m_pInfoButton->SetActivate(false) ;
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
	m_bInfo = m_pInfoButton->BePuton() ;

	Animation() ;
}

void CPlanet::Render()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->SetScale(m_fScale, m_fScale) ;
	m_pSprite->Render() ;
}

void CPlanet::Render_Info()
{
	if(!m_bInfo)
		return ;
	
	SetInfoIndex() ;
	m_pInfo->SetPosition(m_fX, m_fY + 77.0f) ;
	m_pInfo->Render() ;
}

void CPlanet::SetInfoIndex()
{
	int BarrierLevel = g_MapManager->GetMapBarrierLevel(m_MapIndex.x, m_MapIndex.y) ;
	int InfoIndex = m_nProtectLevel - BarrierLevel ;

	if(InfoIndex<0)
		InfoIndex = 0 ;

	m_pInfo->SetTextureUV(100.0f * InfoIndex, 0.0f, 100.0f * (InfoIndex+1), 60.0f) ;
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