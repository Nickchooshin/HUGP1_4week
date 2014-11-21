#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "CameraManager.h"
#include "MusicManager.h"

#include "D3dDevice.h"
#include "Sprite.h"
#include "GameObjectUI.h"

#include "ButtonManager.h"
#include "MapManager.h"

GameScene::GameScene() : m_pBackground(NULL),
						 m_pGameObjectUI(NULL),
						 m_pBGM(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pGameObjectUI!=NULL)
		delete m_pGameObjectUI ;
	
	g_MapManager->ClearMap() ;
}

Scene* GameScene::scene()
{
	Scene *scene = new GameScene ;

	return scene ;
}

void GameScene::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;
	
	g_MapManager->Init() ;
	g_MapManager->LoadMapData() ;

	m_pBackground = new CSprite ;
	switch(g_MapManager->GetMapSize())
	{
	case 3 :
		m_pBackground->Init("Resource/Image/Game/game_bg_S.png") ;
		break ;

	case 6 :
		m_pBackground->Init("Resource/Image/Game/game_bg_M.png") ;
		break ;

	case 9 :
		m_pBackground->Init("Resource/Image/Game/game_bg_L.png") ;
		break ;
	}
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;

	m_pGameObjectUI = new CGameObjectUI ;
	m_pGameObjectUI->Init() ;

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM-03.mp3", true) ;
	g_MusicManager->PlayMusic(m_pBGM, 0) ;
}

void GameScene::Destroy()
{
	g_MusicManager->StopMusic(0) ;
}

void GameScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	g_ButtonManager->Update() ;

	m_pGameObjectUI->Update() ;

	g_MapManager->Update() ;

	//m_pGameObjectUI->Update() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	g_MapManager->Render() ;
	
	m_pGameObjectUI->Render() ;

	g_MapManager->Render_Result() ;
}