#include "TutorialScene.h"

#include "StageScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "CameraManager.h"
#include "MusicManager.h"
#include "SceneManager.h"

#include "D3dDevice.h"
#include "Sprite.h"

#include "MapManager.h"
#include "StageManager.h"

TutorialScene::TutorialScene() : m_nSceneNum(0),
								 m_pBGM(NULL)
{
	for(int i=0; i<7; i++)
		m_pTutorial[i] = NULL ;
}
TutorialScene::~TutorialScene()
{
	for(int i=0; i<7; i++)
	{
		if(m_pTutorial[i]!=NULL)
			delete m_pTutorial[i] ;
	}
}

Scene* TutorialScene::scene()
{
	Scene *scene = new TutorialScene ;

	return scene ;
}

void TutorialScene::Init()
{
	float WinWidth = g_D3dDevice->GetWinWidth() ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;
	char filepath[100] ;

	g_CameraManager->AddCamera(new CCamera(), 0) ;

	for(int i=0; i<7; i++)
	{
		wsprintf(filepath, "Resource/Image/Tutorial/tutorial_%02d.png", i+1) ;
		m_pTutorial[i] = new CSprite ;
		m_pTutorial[i]->Init(filepath) ;
		m_pTutorial[i]->SetPosition(WinWidth / 2.0f, WinHeight / 2.0f) ;
	}

	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/BGM-03.mp3", true) ;
	g_MusicManager->PlayMusic(m_pBGM, 0) ;
}

void TutorialScene::Destroy()
{
	g_MusicManager->StopMusic(0) ;
}

void TutorialScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(g_Mouse->IsMousePress(g_Mouse->LBUTTON_DOWN))
	{
		++m_nSceneNum ;

		if(m_nSceneNum==7)
		{
			g_StageManager->OpenStage(1) ;
			g_SceneManager->ChangeScene(StageScene::scene()) ;
			return ;
		}
	}
}

void TutorialScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pTutorial[m_nSceneNum]->Render() ;
}