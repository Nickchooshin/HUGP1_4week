#pragma once

#include "Singleton.h"

class CStageManager : public Singleton<CStageManager>
{
private :
	int m_nOpenStageNum ;

public :
	CStageManager() ;
	~CStageManager() ;

	const int GetOpenStageNum() const ;

	void LoadStageDat() ;
	void SaveStageDat() ;

	void OpenStage(int StageNum) ;
} ;

#define g_StageManager CStageManager::GetInstance()