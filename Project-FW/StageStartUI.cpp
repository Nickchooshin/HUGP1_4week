#include "StageStartUI.h"
#include "Sprite.h"

#include "D3dDevice.h"
#include "MusicManager.h"

CStageStartUI::CStageStartUI() : m_pBlack(NULL),
								 m_pStageStart(NULL),
								 m_pEStageStart(NULL),
								 m_nState(0),
								 m_fTime(0.0f),
								 m_bStageStartEnd(false)
{
}
CStageStartUI::~CStageStartUI()
{
	if(m_pBlack!=NULL)
		delete m_pBlack ;
	if(m_pStageStart!=NULL)
		delete m_pStageStart ;
}

void CStageStartUI::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBlack = new CSprite ;
	m_pBlack->Init("Resource/Image/Black.png") ;
	m_pBlack->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;
	m_pBlack->SetAlpha(0) ;

	m_pStageStart = new CSprite ;
	m_pStageStart->Init("Resource/Image/Game/UI/Stt_txt.png") ;
	m_pStageStart->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;
	m_pStageStart->SetAlpha(0) ;

	m_pEStageStart = g_MusicManager->LoadMusic("Resource/Sound/SE_start.mp3", false, false) ;
}

const bool CStageStartUI::BeStageStartEnd() const
{
	return m_bStageStartEnd ;
}

void CStageStartUI::Update()
{
	m_fTime += g_D3dDevice->GetTime() ;

	if(m_nState==0)
	{
		m_pBlack->SetAlpha((int)((m_fTime / 0.5f) * 127.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_nState = 1 ;
			m_fTime = 0.0f ;
		}
	}
	else if(m_nState==1)
	{
		m_pStageStart->SetAlpha((int)((m_fTime / 0.5f) * 255.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_nState = 2 ;
			m_fTime = 0.0f ;

			g_MusicManager->PlayMusic(m_pEStageStart, 1) ;
		}
	}
	else if(m_nState==2)
	{
		if(m_fTime>=0.5f)
		{
			m_nState = 3 ;
			m_fTime = 0.0f ;
		}
	}
	else if(m_nState==3)
	{
		m_pStageStart->SetAlpha(255 - (int)((m_fTime / 0.5f) * 255.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_nState = 4 ;
			m_fTime = 0.0f ;
		}
	}
	else if(m_nState==4)
	{
		m_pBlack->SetAlpha(127 - (int)((m_fTime / 0.5f) * 127.0f)) ;

		if(m_fTime>=0.5f)
		{
			m_nState = 5 ;
			m_fTime = 0.0f ;
			m_bStageStartEnd = true ;
		}
	}
}

void CStageStartUI::Render()
{
	m_pBlack->Render() ;

	m_pStageStart->Render() ;
}