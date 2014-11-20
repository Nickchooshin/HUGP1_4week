#include "ResultUI.h"

#include "D3dDevice.h"
#include "Sprite.h"
#include "Button.h"

#include "ButtonManager.h"
#include "MapManager.h"
#include "SceneManager.h"
#include "StageScene.h"
#include "GameScene.h"

CResultUI::CResultUI() : m_nResult(0),
						 m_pBackground(NULL),
						 m_pResult(NULL),
						 m_pFinishButton(NULL),
						 m_pNextStageButton(NULL),
						 m_pRetryButton(NULL),
						 m_pStageSelectButton(NULL),
						 m_fTime(0.0f),
						 m_nState(0)
{
}
CResultUI::~CResultUI()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pResult!=NULL)
		delete m_pResult ;
	if(m_pFinishButton!=NULL)
		g_ButtonManager->DeleteButton(m_pFinishButton) ;
	if(m_pNextStageButton!=NULL)
		g_ButtonManager->DeleteButton(m_pNextStageButton) ;
	if(m_pRetryButton!=NULL)
		g_ButtonManager->DeleteButton(m_pRetryButton) ;
	if(m_pStageSelectButton!=NULL)
		g_ButtonManager->DeleteButton(m_pStageSelectButton) ;
}

void CResultUI::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Black.png") ;
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;

	m_pResult = new CSprite ;
	m_pResult->Init(360.0f, 50.0f, "Resource/Image/Game/Result/Rst_txt.png") ;
	m_pResult->SetPosition(WinWidth / 2.0f, WinHeight - 210.0f) ;

	m_pFinishButton = new CButton ;
	m_pFinishButton->Init(180.0f, 52.0f, "Resource/Image/Game/Result/Rst_btn_finish.png") ;
	m_pFinishButton->SetPosition(WinWidth / 2.0f, WinHeight - 350.0f) ;
	m_pFinishButton->SetIndex(0, 1, 0, 0) ;
	m_pFinishButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pFinishButton) ;

	m_pNextStageButton = new CButton ;
	m_pNextStageButton->Init(180.0f, 52.0f, "Resource/Image/Game/Result/Rst_btn_nextstage.png") ;
	m_pNextStageButton->SetPosition(WinWidth / 2.0f, WinHeight - 350.0f) ;
	m_pNextStageButton->SetIndex(0, 1, 0, 0) ;
	m_pNextStageButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pNextStageButton) ;

	m_pRetryButton = new CButton ;
	m_pRetryButton->Init(180.0f, 52.0f, "Resource/Image/Game/Result/Rst_btn_retry.png") ;
	m_pRetryButton->SetPosition(WinWidth / 2.0f, WinHeight - 350.0f) ;
	m_pRetryButton->SetIndex(0, 1, 0, 0) ;
	m_pRetryButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pRetryButton) ;

	m_pStageSelectButton = new CButton ;
	m_pStageSelectButton->Init(180.0f, 52.0f, "Resource/Image/Game/Result/Rst_btn_stageselect.png") ;
	m_pStageSelectButton->SetPosition(WinWidth / 2.0f, WinHeight - 440.0f) ;
	m_pStageSelectButton->SetIndex(0, 1, 0, 0) ;
	m_pStageSelectButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pStageSelectButton) ;
}

void CResultUI::InitValue()
{
	m_nResult = 0 ;
	m_fTime = 0.0f ;
	m_nState = 0 ;

	m_pBackground->SetAlpha(0) ;
}

void CResultUI::SetResult(int Result)
{
	m_nResult = Result ;

	m_pResult->SetTextureUV(360.0f * (m_nResult-1), 0.0f, 360.0f * m_nResult, 50.0f) ;
}

void CResultUI::Update()
{
	if(m_nState!=2)
	{
		m_fTime += g_D3dDevice->GetTime() ;

		if(m_nState==0)
		{
			if(m_fTime>=2.0f)
			{
				m_nState = 1 ;
				m_fTime = 0.0f ;
			}
		}
		else if(m_nState==1)
		{
			m_pBackground->SetAlpha((int)((m_fTime / 0.5f) * 127.0f)) ;

			if(m_fTime>=0.5f)
			{
				m_nState = 2 ;
				m_fTime = 0.0f ;
			}
		}
	}
	else
	{
		if(m_nResult==3 && m_pFinishButton->BeClick())
		{
			return ;
		}
		else if(m_nResult==1 && m_pNextStageButton->BeClick())
		{
			g_MapManager->SetMapNumber(g_MapManager->GetMapNumber()+1) ;
			g_SceneManager->ChangeScene(GameScene::scene()) ;
			return ;
		}
		else if(m_nResult==2 && m_pRetryButton->BeClick())
		{
			g_SceneManager->ChangeScene(GameScene::scene()) ;
			return ;
		}
		else if((m_nResult==1 || m_nResult==2) && m_pStageSelectButton->BeClick())
		{
			g_SceneManager->ChangeScene(StageScene::scene()) ;
			return ;
		}
	}
}

void CResultUI::Render()
{
	m_pBackground->Render() ;

	if(m_nState==2)
	{
		m_pResult->Render() ;

		switch(m_nResult)
		{
		case 1 :
			m_pNextStageButton->Render() ;
			m_pStageSelectButton->Render() ;
			break ;

		case 2 :
			m_pRetryButton->Render() ;
			m_pStageSelectButton->Render() ;
			break ;

		case 3 :
			m_pFinishButton->Render() ;
			break ;
		}
	}
}