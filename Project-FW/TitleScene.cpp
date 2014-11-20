#include "TitleScene.h"

#include "StageScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "D3dDevice.h"
#include "Sprite.h"
#include "Button.h"

#include "ButtonManager.h"
#include "LineEffectManager.h"

TitleScene::TitleScene() : m_pBackground(NULL),
						   m_pTitle(NULL),
						   m_pStartButton(NULL), m_pExitButton(NULL)
{
}
TitleScene::~TitleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pTitle!=NULL)
		delete m_pTitle ;
	if(m_pStartButton!=NULL)
		g_ButtonManager->DeleteButton(m_pStartButton) ;
	if(m_pExitButton!=NULL)
		g_ButtonManager->DeleteButton(m_pExitButton) ; 
}

Scene* TitleScene::scene()
{
	Scene *scene = new TitleScene ;

	return scene ;
}

void TitleScene::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Title/Main_bg.jpg") ;
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;

	m_pTitle = new CSprite ;
	m_pTitle->Init(430.0f, 30.0f, "Resource/Image/Title/Main_title.png") ;
	m_pTitle->SetPosition(288.0f, WinHeight - 134.0f) ;
	m_pTitle->SetTextureUV(0.0f, 0.0f, 430.0f, 30.0f) ;

	m_pStartButton = new CButton ;
	m_pStartButton->Init(234.0f, 64.0f, "Resource/Image/Title/Main_btn_start.png") ;
	m_pStartButton->SetPosition(288.0f, WinHeight - 570.0f) ;
	m_pStartButton->SetIndex(0, 1, 0, 0) ;
	m_pStartButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pStartButton) ;

	m_pExitButton = new CButton ;
	m_pExitButton->Init(234.0f, 64.0f, "Resource/Image/Title/Main_btn_exit.png") ;
	m_pExitButton->SetPosition(288.0f, WinHeight - 670.0f) ;
	m_pExitButton->SetIndex(0, 1, 0, 0) ;
	m_pExitButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pExitButton) ;
}

void TitleScene::Destroy()
{
}

void TitleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ButtonManager->Update() ;

	g_LineEffectManager->Update() ;

	if(m_pStartButton->BeClick())
	{
		g_SceneManager->ChangeScene(StageScene::scene()) ;
		return ;
	}
	else if(m_pExitButton->BeClick())
	{
		PostQuitMessage(0) ;
		return ;
	}
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	g_LineEffectManager->Render() ;

	m_pTitle->Render() ;

	m_pStartButton->Render() ;
	m_pExitButton->Render() ;
}