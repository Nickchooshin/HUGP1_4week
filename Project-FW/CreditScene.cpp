#include "CreditScene.h"

#include "TitleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "D3dDevice.h"
#include "Sprite.h"

CreditScene::CreditScene() : m_pBackground(NULL),
							 m_pText(NULL),
							 m_pBlack(NULL),
							 m_fY(0.0f), m_fYMax(0.0f),
							 m_nState(0),
							 m_fTime(0.0f),
							 m_bReturnTitle(false)
{
}
CreditScene::~CreditScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pText!=NULL)
		delete m_pText ;
	if(m_pBlack!=NULL)
		delete m_pBlack ;
}

Scene* CreditScene::scene()
{
	Scene *scene = new CreditScene ;

	return scene ;
}

void CreditScene::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_fY = -756.0f ;
	m_fYMax = WinHeight + 756.0f ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Credit/crd_bg.png") ;
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;

	m_pText = new CSprite ;
	m_pText->Init("Resource/Image/Credit/crd_txt.png") ;
	m_pText->SetPosition(WinWidth / 2.0f, m_fY) ;

	m_pBlack = new CSprite ;
	m_pBlack->Init("Resource/Image/Black.png") ;
	m_pBlack->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;
	m_pBlack->SetAlpha(0) ;
}

void CreditScene::Destroy()
{
}

void CreditScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(m_fY<=m_fYMax)
	{
		float fSpeed = g_D3dDevice->GetMoveTime() * 1.5f ;
		float x = g_D3dDevice->GetWinWidth() / 2.0f ;

		m_fY += fSpeed ;

		m_pText->SetPosition(x, m_fY) ;
	}
	else
		m_bReturnTitle = true ;

	if(m_bReturnTitle)
	{
		m_fTime += g_D3dDevice->GetTime() ;

		if(m_nState==0)
		{
			if(m_fTime>=5.0f)
			{
				m_nState = 1 ;
				m_fTime = 0.0f ;
			}
			else
				m_pBlack->SetAlpha((int)((m_fTime / 5.0f) * 255.0f)) ;
		}
		else if(m_nState==1)
		{
			if(m_fTime>=3.0f)
			{
				g_SceneManager->ChangeScene(TitleScene::scene()) ;
				return ;
			}
		}
	}
	else
	{
		if(g_Mouse->IsMousePress(g_Mouse->LBUTTON_DOWN))
			m_bReturnTitle = true ;
	}
}

void CreditScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	m_pText->Render() ;

	m_pBlack->Render() ;
}