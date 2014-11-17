#pragma once

#include "Singleton.h"

class CMapManager : public Singleton<CMapManager>
{
private :
	int **m_pMap ;
	int m_nMapNumber ;
	int m_nMapSize ;

public :
	CMapManager() ;
	~CMapManager() ;

	void SetMapNumber(int num) ;

	void LoadMapData() ;

	void ClearMap() ;
} ;

#define g_MapManager CMapManager::GetInstance()