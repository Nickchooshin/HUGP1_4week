#include "StageScene.h"

#include "TitleScene.h"
#include "GameScene.h"

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
#include "StageManager.h"
#include "MapManager.h"

StageScene::StageScene() : m_pBackground(NULL),
						   m_pNextButton(NULL), m_pPrevButton(NULL),
						   m_pStageSelect(NULL)
{
	for(int i=0; i<20; i++)
	{
		m_pStageNumber[i] = NULL ;
		m_pStageButton[i] = NULL ;
	}
}
StageScene::~StageScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pNextButton!=NULL)
		g_ButtonManager->DeleteButton(m_pNextButton) ;
	if(m_pPrevButton!=NULL)
		g_ButtonManager->DeleteButton(m_pPrevButton) ;
	if(m_pStageSelect!=NULL)
		delete m_pStageSelect ;

	for(int i=0; i<20; i++)
	{
		if(m_pStageNumber[i]!=NULL)
			delete m_pStageNumber[i] ;
	}
}

Scene* StageScene::scene()
{
	Scene *scene = new StageScene ;

	return scene ;
}

void StageScene::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Stage/Stage_bg.png") ;
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;

	m_pNextButton = new CButton ;
	m_pNextButton->Init(76.0f, 60.0f, "Resource/Image/Stage/Stage_btn_next.png") ;
	m_pNextButton->SetPosition(504.0f, WinHeight - 76.0f) ;
	m_pNextButton->SetIndex(0, 1, 0, 0) ;
	m_pNextButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pNextButton) ;

	m_pPrevButton = new CButton ;
	m_pPrevButton->Init(76.0f, 60.0f, "Resource/Image/Stage/Stage_btn_prev.png") ;
	m_pPrevButton->SetPosition(72.0f, WinHeight - 76.0f) ;
	m_pPrevButton->SetIndex(0, 1, 0, 0) ;
	m_pPrevButton->SetPutonActivate(true) ;
	g_ButtonManager->AddButton(m_pPrevButton) ;

	g_StageManager->LoadStageDat() ;

	m_pStageSelect = new CSprite ;
	m_pStageSelect->Init(90.0f, 90.0f, "Resource/Image/Stage/Stage_btn_list.png") ;
	m_pStageSelect->SetTextureUV(0.0f, 0.0f, 90.0f, 90.0f) ;

	char filepath[100] ;
	float x, y ;
	const int OpenStageNum = g_StageManager->GetOpenStageNum() ;
	const int MapNumber = g_MapManager->GetMapNumber() ;

	for(int i=0; i<20; i++)
	{
		x = 108.0f + ((i%4) * (90.0f + 30.0f)) ;
		y = WinHeight - (200.0f + ((i/4) * (90.0f + 34.0f))) ;

		wsprintf(filepath, "Resource/Image/Stage/Stage_n_%02d.png", i) ;
		m_pStageNumber[i] = new CSprite ;
		m_pStageNumber[i]->Init(filepath) ;
		m_pStageNumber[i]->SetPosition(x, y) ;

		m_pStageButton[i] = new CButton ;
		m_pStageButton[i]->Init(90.0f, 90.0f, "Resource/Image/Stage/Stage_btn_list.png") ;
		m_pStageButton[i]->SetIndex(1, 1, 1, 2) ;
		m_pStageButton[i]->SetPosition(x, y) ;
		m_pStageButton[i]->SetActivate(i<=OpenStageNum) ;
		g_ButtonManager->AddButton(m_pStageButton[i]) ;

		if(i==MapNumber)
			m_pStageSelect->SetPosition(x, y) ;
	}
}

void StageScene::Destroy()
{
}

void StageScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ButtonManager->Update() ;

	if(m_pNextButton->BeClick())
	{
		g_SceneManager->ChangeScene(GameScene::scene()) ;
		return ;
	}
	else if(m_pPrevButton->BeClick())
	{
		g_SceneManager->ChangeScene(TitleScene::scene()) ;
		return ;
	}

	for(int i=0; i<20; i++)
	{
		if(m_pStageButton[i]->BeClick())
		{
			float WinHeight = g_D3dDevice->GetWinHeight() ;
			float x = 108.0f + ((i%4) * (90.0f + 30.0f)) ;
			float y = WinHeight - (200.0f + ((i/4) * (90.0f + 34.0f))) ;

			g_MapManager->SetMapNumber(i) ;
			m_pStageSelect->SetPosition(x, y) ;
		}
	}
}

void StageScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	m_pNextButton->Render() ;
	m_pPrevButton->Render() ;

	const int MapNumber = g_MapManager->GetMapNumber() ;

	for(int i=0; i<20; i++)
	{
		m_pStageButton[i]->Render() ;

		if(i==MapNumber)
			m_pStageSelect->Render() ;

		if(m_pStageButton[i]->BeActivate())
			m_pStageNumber[i]->Render() ;
	}
}