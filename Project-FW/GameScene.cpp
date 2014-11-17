#include "GameScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "CameraManager.h"
#include "MusicManager.h"

#include "D3dDevice.h"
#include "Sprite.h"

#include "MapManager.h"

GameScene::GameScene() : m_pBackground(NULL)
{
}
GameScene::~GameScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
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

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Title/Main_01.jpg") ;
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;

	g_MapManager->SetMapNumber(1) ;
	g_MapManager->LoadMapData() ;
}

void GameScene::Destroy()
{
}

void GameScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;
}

void GameScene::Render()
{
	g_CameraManager->CameraRun() ;

	//m_pBackground->Render() ;
}