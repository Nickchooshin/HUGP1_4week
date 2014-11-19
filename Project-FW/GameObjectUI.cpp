#include "GameObjectUI.h"

#include "D3dDevice.h"
#include "Sprite.h"
#include "Button.h"
#include "NumberUI.h"

#include "ButtonManager.h"
#include "MapManager.h"

CGameObjectUI::CGameObjectUI() : m_pStageNumber(NULL),
								 m_pOperateButton(NULL)
{
	for(int i=0; i<5; i++)
	{
		m_pBarrierButton[i] = NULL ;
		m_pBarrierNum[i] = NULL ;
	}
}
CGameObjectUI::~CGameObjectUI()
{
	if(m_pStageNumber!=NULL)
		delete m_pStageNumber ;
	if(m_pOperateButton!=NULL)
		g_ButtonManager->DeleteButton(m_pOperateButton) ;

	for(int i=0; i<5; i++)
	{
		if(m_pBarrierButton[i]!=NULL)
			g_ButtonManager->DeleteButton(m_pBarrierButton[i]) ;
		if(m_pBarrierNum[i]!=NULL)
			delete m_pBarrierNum[i] ;
	}
}

void CGameObjectUI::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	char filepath[100] ;
	wsprintf(filepath, "Resource/Image/Game/UI/Game_stg_%02d.png", g_MapManager->GetMapNumber()) ;

	m_pStageNumber = new CSprite ;
	m_pStageNumber->Init(filepath) ;
	m_pStageNumber->SetPosition(WinWidth / 2.0f, WinHeight - 36.0f) ;

	m_pOperateButton = new CButton ;
	m_pOperateButton->Init(170.0f, 60.0f, "Resource/Image/Game/UI/Game_btn_operate.png") ;
	m_pOperateButton->SetPosition(WinWidth / 2.0f, WinHeight - 650.0f) ;
	m_pOperateButton->SetIndex(0, 0, 1, 0) ;
	g_ButtonManager->AddButton(m_pOperateButton) ;

	for(int i=0; i<5; i++)
	{
		wsprintf(filepath, "Resource/Image/Game/UI/Game_ui_bar_%d.png", i+1) ;
		m_pBarrierButton[i] = new CButton ;
		m_pBarrierButton[i]->Init(108.0f, 62.0f, filepath) ;
		m_pBarrierButton[i]->SetPosition(72.0f + (i * 144.0f), WinHeight - 737.0f) ;
		m_pBarrierButton[i]->SetIndex(0, 0, 0, 0) ;
		g_ButtonManager->AddButton(m_pBarrierButton[i]) ;

		m_pBarrierNum[i] = new CNumberUI ;
		m_pBarrierNum[i]->Init() ;
		m_pBarrierNum[i]->SetPosition(108.0f + (i * 144.0f), WinHeight - 737.0f) ;
		m_pBarrierNum[i]->SetNumber(i) ;
	}
}

void CGameObjectUI::Update()
{
}

void CGameObjectUI::Render()
{
	m_pStageNumber->Render() ;

	m_pOperateButton->Render() ;

	for(int i=0; i<5; i++)
	{
		m_pBarrierButton[i]->Render() ;
		m_pBarrierNum[i]->Render() ;
	}
}