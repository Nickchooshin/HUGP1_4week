#include "StageScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "CameraManager.h"
#include "MusicManager.h"

#include "D3dDevice.h"
#include "Sprite.h"

StageScene::StageScene() : m_pBackground(NULL)
{
}
StageScene::~StageScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
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
	m_pBackground->Init("Resource/Image/Title/Main_01.jpg") ;
	m_pBackground->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;
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
}

void StageScene::Render()
{
	g_CameraManager->CameraRun() ;

	//m_pBackground->Render() ;
}