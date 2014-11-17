#include "MapManager.h"
#include <stdio.h>
#include <windows.h>

CMapManager::CMapManager() : m_pMap(NULL),
							 m_nMapNumber(0),
							 m_nMapSize(0)
{
}
CMapManager::~CMapManager()
{
	ClearMap() ;
}

void CMapManager::SetMapNumber(int num)
{
	m_nMapNumber = num ;
}

void CMapManager::LoadMapData()
{
	FILE *MapDat ;
	char filepath[100] ;

	wsprintf(filepath, "Resource/Data/Map/%d.dat", m_nMapNumber) ;

	MapDat = fopen(filepath, "r") ;
	if(MapDat==NULL)
	{
		MessageBox(NULL, "%s 파일을 열 수 없습니다.", "Error", MB_OK) ;
		return ;
	}

	fscanf(MapDat, "%d\n", &m_nMapSize) ;

	m_pMap = new int*[m_nMapSize] ;

	for(int i=0; i<m_nMapSize; i++)
	{
		m_pMap[i] = new int[m_nMapSize] ;

		for(int j=0; j<m_nMapSize; j++)
		{
			fscanf(MapDat, "%d ", &m_pMap[i][j]) ;
		}
	}

	fclose(MapDat) ;
}

void CMapManager::ClearMap()
{
	if(m_pMap!=NULL)
	{
		for(int i=0; i<m_nMapSize; i++)
			delete[] m_pMap[i] ;

		delete[] m_pMap ;
	}
}