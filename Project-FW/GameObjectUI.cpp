#include "GameObjectUI.h"

#include "D3dDevice.h"
#include "Sprite.h"
#include "Button.h"
#include "NumberUI.h"
#include "BarrierButtonUI.h"

#include "Mouse.h"

#include "ButtonManager.h"
#include "MapManager.h"

CGameObjectUI::CGameObjectUI() : m_nSelectedType(0), m_nSelectedIndex(-1),
								 m_bMapGrid(false),
								 m_pSelectedBarrier(NULL),
								 m_pMapGrid(NULL),
								 m_pStageNumber(NULL),
								 m_pOperateButton(NULL),
								 m_fObjectScale(1.0f)
{
	for(int i=0; i<4; i++)
		m_pBarrierButtonUI[i] = NULL ;
}
CGameObjectUI::~CGameObjectUI()
{
	if(m_pMapGrid!=NULL)
		delete m_pMapGrid ;
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
	int BarrierType[4], BarrierNum[4] ;

	LoadBarrierDat(BarrierType, BarrierNum) ;

	m_pMapGrid = new CSprite ;
	m_pMapGrid->Init("Resource/Image/Game/Game_map_grid.png") ;

	wsprintf(filepath, "Resource/Image/Game/UI/Game_stg_%02d.png", g_MapManager->GetMapNumber()) ;
	m_pStageNumber = new CSprite ;
	m_pStageNumber->Init(filepath) ;
	m_pStageNumber->SetPosition(WinWidth / 2.0f, WinHeight - 36.0f) ;

	m_pOperateButton = new CButton ;
	m_pOperateButton->Init(170.0f, 60.0f, "Resource/Image/Game/UI/Game_btn_operate.png") ;
	m_pOperateButton->SetPosition(WinWidth / 2.0f, WinHeight - 650.0f) ;
	m_pOperateButton->SetIndex(0, 0, 1, 0) ;
	m_pOperateButton->SetClickDownSound("Resource/Sound/SE_select.mp3") ;
	m_pOperateButton->SetPutonSound("Resource/Sound/SE_button.mp3") ;
	g_ButtonManager->AddButton(m_pOperateButton) ;

	for(int i=0; i<4; i++)
	{
		m_pBarrierButtonUI[i] = new CBarrierButtonUI ;
		m_pBarrierButtonUI[i]->Init(BarrierType[i], BarrierNum[i]) ;
		m_pBarrierButtonUI[i]->SetPosition(72.0f + (i * 144.0f), WinHeight - 737.0f) ;
	}

	InitScale() ;
}

void CGameObjectUI::InitScale()
{
	switch(g_MapManager->GetMapSize())
	{
	case 3 :
		m_fObjectScale = 1.0f ;
		break ;

	case 6 :
		m_fObjectScale = 0.5f ;
		break ;

	case 9 :
		m_fObjectScale = 0.3375f ;
		break ;
	}
}

void CGameObjectUI::Update()
{
	for(int i=0; i<4; i++)
	{
		m_pBarrierButtonUI[i]->Update() ;

		if(m_pBarrierButtonUI[i]->BeClick())
		{
			m_nSelectedType = m_pBarrierButtonUI[i]->GetType() ;
			m_nSelectedIndex = i ;
			m_pSelectedBarrier = m_pBarrierButtonUI[i]->GetSelectedSprite() ;
		}
	}

	if(g_Mouse->IsMousePress(g_Mouse->RBUTTON_DOWN))
		ClearSelectedBarrier() ;

	if(m_nSelectedType!=0)
	{
		float x = g_Mouse->GetMousePoint().x ;
		float y = g_Mouse->GetMousePoint().y ;
		float IndexPosX, IndexPosY ;

		m_pSelectedBarrier->SetPosition(x, y) ;

		m_bMapGrid = g_MapManager->InMapArea(x, y, IndexPosX, IndexPosY) ;

		if(m_bMapGrid)
		{
			m_pMapGrid->SetPosition(IndexPosX, IndexPosY) ;

			if(g_Mouse->IsMousePress(g_Mouse->LBUTTON_DOWN))
			{
				if(g_MapManager->BuildBarrier(m_nSelectedType, IndexPosX, IndexPosY))
				{
					m_pBarrierButtonUI[m_nSelectedIndex]->SubBarrierNum() ;
					ClearSelectedBarrier() ;
				}
			}
		}
	}

	//

	if(m_pOperateButton->BeClick())
	{
		for(int i=0; i<4; i++)
			m_pBarrierButtonUI[i]->SetActivate(false) ;
		m_pOperateButton->SetActivate(false) ;
		g_MapManager->Operate() ;
	}
}

void CGameObjectUI::Render()
{
	if(m_nSelectedType!=0 && m_bMapGrid)
	{
		m_pMapGrid->SetScale(m_fObjectScale, m_fObjectScale) ;
		m_pMapGrid->Render() ;
	}

	m_pStageNumber->Render() ;

	m_pOperateButton->Render() ;

	for(int i=0; i<4; i++)
		m_pBarrierButtonUI[i]->Render() ;

	if(m_nSelectedType!=0)
	{
		m_pSelectedBarrier->SetScale(m_fObjectScale, m_fObjectScale) ;
		m_pSelectedBarrier->Render() ;
	}
}

void CGameObjectUI::LoadBarrierDat(int *BarrierType, int *BarrierNum)
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
		fscanf(BarrierDat, "%d %d\n", &BarrierType[i], &BarrierNum[i]) ;

	fclose(BarrierDat) ;
}

void CGameObjectUI::ClearSelectedBarrier()
{
	m_nSelectedType = 0 ;
	m_nSelectedIndex = -1 ;
	m_pSelectedBarrier = NULL ;
}