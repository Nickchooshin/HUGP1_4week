#include "BarrierButtonUI.h"

#include "Sprite.h"
#include "Button.h"
#include "NumberUI.h"

#include "D3dDevice.h"
#include "ButtonManager.h"

CBarrierButtonUI::CBarrierButtonUI() : m_nType(0), m_nNum(0),
									   m_bPuton(false),
									   m_pButton(NULL),
									   m_pSelectedSprite(NULL),
									   m_pInfo(NULL),
									   m_pNumberUI(NULL)
{
}
CBarrierButtonUI::~CBarrierButtonUI()
{
	if(m_pButton!=NULL)
		g_ButtonManager->DeleteButton(m_pButton) ;
	if(m_pInfo!=NULL)
		delete m_pInfo ;
	if(m_pSelectedSprite!=NULL)
		delete m_pSelectedSprite ;
	if(m_pNumberUI!=NULL)
		delete m_pNumberUI ;
}

void CBarrierButtonUI::Init(int Type, int Num)
{
	float WinHeight = g_D3dDevice->GetWinHeight() ;
	char filepath[100] ;

	m_nType = Type ;
	m_nNum = Num ;

	wsprintf(filepath, "Resource/Image/Game/UI/Game_ui_bar_%d.png", m_nType) ;
	m_pButton = new CButton ;
	m_pButton->Init(108.0f, 62.0f, filepath) ;
	m_pButton->SetIndex(0, 0, 0, 0) ;
	m_pButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pButton) ;

	wsprintf(filepath, "Resource/Image/Game/UI/Game_bar_info_%d.png", m_nType) ;
	m_pInfo = new CSprite ;
	m_pInfo->Init(filepath) ;

	wsprintf(filepath, "Resource/Image/Game/UI/Game_bar_mouse_%d.png", m_nType) ;
	m_pSelectedSprite = new CSprite ;
	m_pSelectedSprite->Init(filepath) ;

	m_pNumberUI = new CNumberUI ;
	m_pNumberUI->Init() ;
	m_pNumberUI->SetNumber(m_nNum) ;
}

void CBarrierButtonUI::SetPosition(float fX, float fY)
{
	m_pButton->SetPosition(fX, fY) ;
	m_pInfo->SetPosition(fX, fY + 92.0f) ;
	m_pNumberUI->SetPosition(fX + 36.0f, fY) ;
}

void CBarrierButtonUI::SetActivate(bool bActivate)
{
	m_pButton->SetActivate(bActivate) ;
}

void CBarrierButtonUI::SubBarrierNum()
{
	--m_nNum ;
}

const int CBarrierButtonUI::GetType() const
{
	return m_nType ;
}

CSprite* CBarrierButtonUI::GetSelectedSprite() const
{
	return m_pSelectedSprite ;
}

const bool CBarrierButtonUI::BeClick() const
{
	return (m_nNum!=0) && m_pButton->BeClick() ;
}

void CBarrierButtonUI::Update()
{
	m_pNumberUI->SetNumber(m_nNum) ;

	m_bPuton = m_pButton->BePuton() ;
}

void CBarrierButtonUI::Render()
{
	m_pButton->Render() ;
	m_pNumberUI->Render() ;

	if(m_bPuton)
		m_pInfo->Render() ;
}