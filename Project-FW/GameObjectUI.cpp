#include "GameObjectUI.h"

#include "D3dDevice.h"
#include "Sprite.h"
#include "Button.h"
#include "NumberUI.h"
#include "BarrierButtonUI.h"

#include "ButtonManager.h"
#include "MapManager.h"

CGameObjectUI::CGameObjectUI() : m_pStageNumber(NULL),
								 m_pOperateButton(NULL)
{
	for(int i=0; i<4; i++)
	{
		m_nBarrierType[i] = 0 ;
		m_nBarrierNum[i] = 0 ;
		m_pBarrierButtonUI[i] = NULL ;
	}
}
CGameObjectUI::~CGameObjectUI()
{
	if(m_pStageNumber!=NULL)
		delete m_pStageNumber ;
	if(m_pOperateButton!=NULL)
		g_ButtonManager->DeleteButton(m_pOperateButton) ;

	for(int i=0; i<4; i++)
	{
		if(m_pBarrierButtonUI[i]!=NULL)
			delete m_pBarrierButtonUI[i] ;
	}
}

void CGameObjectUI::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;
	char filepath[100] ;
	

	LoadBarrierDat() ;

	wsprintf(filepath, "Resource/Image/Game/UI/Game_stg_%02d.png", g_MapManager->GetMapNumber()) ;
	m_pStageNumber = new CSprite ;
	m_pStageNumber->Init(filepath) ;
	m_pStageNumber->SetPosition(WinWidth / 2.0f, WinHeight - 36.0f) ;

	m_pOperateButton = new CButton ;
	m_pOperateButton->Init(170.0f, 60.0f, "Resource/Image/Game/UI/Game_btn_operate.png") ;
	m_pOperateButton->SetPosition(WinWidth / 2.0f, WinHeight - 650.0f) ;
	m_pOperateButton->SetIndex(0, 0, 1, 0) ;
	g_ButtonManager->AddButton(m_pOperateButton) ;

	for(int i=0; i<4; i++)
	{
		m_pBarrierButtonUI[i] = new CBarrierButtonUI ;
		m_pBarrierButtonUI[i]->Init(m_nBarrierType[i], m_nBarrierNum[i]) ;
		m_pBarrierButtonUI[i]->SetPosition(72.0f + (i * 144.0f), WinHeight - 737.0f) ;
	}
}

void CGameObjectUI::Update()
{
	for(int i=0; i<4; i++)
		m_pBarrierButtonUI[i]->Update() ;
}

void CGameObjectUI::Render()
{
	m_pStageNumber->Render() ;

	m_pOperateButton->Render() ;

	for(int i=0; i<4; i++)
		m_pBarrierButtonUI[i]->Render() ;
}

void CGameObjectUI::LoadBarrierDat()
{
	FILE *BarrierDat ;
	char filepath[100] ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	wsprintf(filepath, "Resource/Data/Barrier/%d.dat", g_MapManager->GetMapNumber()) ;

	BarrierDat = fopen(filepath, "r") ;
	if(BarrierDat==NULL)
	{
		char str[1024] ;
		wsprintf(str, "%s 파일을 열 수 없습니다.", filepath) ;
		MessageBox(NULL, str, "Error", MB_OK) ;
		return ;
	}

	for(int i=0; i<4; i++)
		fscanf(BarrierDat, "%d %d\n", &m_nBarrierType[i], &m_nBarrierNum[i]) ;

	fclose(BarrierDat) ;
}