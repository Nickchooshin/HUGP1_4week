#include "MapManager.h"
#include <stdio.h>
#include <windows.h>
#include "D3dDevice.h"

#include "Barrier.h"
#include "Planet.h"

CMapManager::CMapManager() : m_nMapNumber(0),
							 m_nMapSize(0)
{
	int i, j ;

	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			m_nMap[i][j] = 0 ;
			m_nMapBarrier[i][j] = 0 ;
		}
	}

	m_fMapStartXY[0][0] = 151.0f ; m_fMapStartXY[0][1] = 247.0f ;
	m_fMapStartXY[1][0] = 117.0f ; m_fMapStartXY[1][1] = 213.0f ;
	m_fMapStartXY[2][0] = 106.0f ; m_fMapStartXY[2][1] = 202.0f ;

	m_fMapSpace[0] = 136.0f ;
	m_fMapSpace[1] = 68.0f ;
	m_fMapSpace[2] = 46.0f ;
}
CMapManager::~CMapManager()
{
	ClearMap() ;
}

void CMapManager::SetMapNumber(int num)
{
	m_nMapNumber = num ;
}

bool CMapManager::SetBarrier(CBarrier *pBarrier, int IndexX, int IndexY)
{
	if(m_nMap[IndexX][IndexY]!=0)
		return false ;

	int i ;
	const int num = pBarrier->GetBarrierAreaNum() ;
	const POSITION *pArea = pBarrier->GetBarrierArea() ;

	for(i=0; i<num; i++)
	{
		int x = IndexX + pArea[i].x ;
		int y = IndexY + pArea[i].y ;

		if( (x<0 || x>m_nMapSize) ||
			(y<0 || y>m_nMapSize) )
			continue ;

		m_nMapBarrier[pArea[i].x][pArea[i].y] += 1 ;
	}

	m_nMap[IndexX][IndexY] = -1 ;

	m_BarrierList.push_back(pBarrier) ;

	return true ;
}

bool CMapManager::BuildBarrier(int Type, float IndexPosX, float IndexPosY)
{
	CBarrier *pBarrier ;
	int IndexX, IndexY ;
	const int MapIndex = (m_nMapSize/3)-1 ;

	IndexX = (int)(IndexPosX - m_fMapStartXY[MapIndex][0]) / (int)(m_fMapSpace[MapIndex]) ;
	IndexY = (int)(IndexPosY - m_fMapStartXY[MapIndex][1]) / (int)(m_fMapSpace[MapIndex]) ;
	IndexY = (m_nMapSize-1) - IndexY ;

	pBarrier = new CBarrier ;
	pBarrier->Init(Type) ;
	pBarrier->SetPosition(IndexPosX, IndexPosY) ;

	if(!SetBarrier(pBarrier, IndexX, IndexY))
	{
		delete pBarrier ;
		return false ;
	}

	return true ;
}

const int CMapManager::GetMapSize() const
{
	return m_nMapSize ;
}

const int CMapManager::GetMapNumber() const
{
	return m_nMapNumber ;
}

const bool CMapManager::InMapArea(float x, float y, float &IndexPosX, float &IndexPosY) const
{
	const int MapIndex = (m_nMapSize/3)-1 ;
	const float Space = m_fMapSpace[MapIndex] ;

	float MinX, MinY ;
	float MaxX, MaxY ;

	MinX = m_fMapStartXY[MapIndex][0] - (Space / 2.0f) ;
	MinY = m_fMapStartXY[MapIndex][1] - (Space / 2.0f) ;
	MaxX = MinX + (Space * (m_nMapSize)) ;
	MaxY = MinY + (Space * (m_nMapSize)) ;

	if( (x>=MinX && x<=MaxX) && (y>=MinY && y<=MaxY) )
	{
		for(int i=0; i<m_nMapSize; i++)
		{
			for(int j=0; j<m_nMapSize; j++)
			{
				float X1 = MinX + (Space * j) ;
				float Y1 = MinY + (Space * i) ;
				float X2 = X1 + Space ;
				float Y2 = Y1 + Space ;

				if( (x>=X1 && x<=X2) && (y>=Y1 && y<=Y2) )
				{
					IndexPosX = (X1 + X2) / 2.0f ;
					IndexPosY = (Y1 + Y2) / 2.0f ;
					return true ;
				}
			}
		}
	}

	return false ;
}

void CMapManager::LoadMapData()
{
	FILE *MapDat ;
	char filepath[100] ;
	float WinHeight = g_D3dDevice->GetWinHeight() ;

	wsprintf(filepath, "Resource/Data/Map/%d.dat", m_nMapNumber) ;

	MapDat = fopen(filepath, "r") ;
	if(MapDat==NULL)
	{
		char str[1024] ;
		wsprintf(str, "%s 파일을 열 수 없습니다.", filepath) ;
		MessageBox(NULL, str, "Error", MB_OK) ;
		return ;
	}

	fscanf(MapDat, "%d\n", &m_nMapSize) ;

	const int MapIndex = (m_nMapSize/3)-1 ;
	const float MapSpace = m_fMapSpace[MapIndex] ;
	const float StartX = m_fMapStartXY[MapIndex][0] ;
	const float StartY = m_fMapStartXY[MapIndex][1] ;

	for(int i=0; i<m_nMapSize; i++)
	{
		for(int j=0; j<m_nMapSize; j++)
		{
			fscanf(MapDat, "%d ", &m_nMap[j][i]) ;
			m_nMapBarrier[j][i] = 0 ;

			if(m_nMap[j][i]!=0)
			{
				CPlanet *pPlanet = new CPlanet ;
				pPlanet->Init(m_nMap[j][i]) ;
				pPlanet->SetPosition(StartX + (j * MapSpace), WinHeight - (StartY + (i * MapSpace))) ;
				m_PlanetList.push_back(pPlanet) ;
			}
		}
	}

	fclose(MapDat) ;
}

void CMapManager::ClearMap()
{
	int i, j ;

	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			m_nMap[i][j] = 0 ;
			m_nMapBarrier[i][j] = 0 ;
		}
	}

	int num ;
	
	num = m_PlanetList.size() ;
	for(i=0; i<num; i++)
		delete m_PlanetList[i] ;

	if(num!=0)
		m_PlanetList.clear() ;

	num = m_BarrierList.size() ;
	for(i=0; i<num; i++)
		delete m_BarrierList[i] ;

	if(num!=0)
		m_BarrierList.clear() ;
}

void CMapManager::Update()
{
	int i ;
	int num ;

	num = m_PlanetList.size() ;
	for(i=0; i<num; i++)
		m_PlanetList[i]->Update() ;

	num = m_BarrierList.size() ;
	for(i=0; i<num; i++)
		m_BarrierList[i]->Update() ;
}

void CMapManager::Render()
{
	int i ;
	int num ;

	num = m_PlanetList.size() ;
	for(i=0; i<num; i++)
		m_PlanetList[i]->Render() ;

	num = m_BarrierList.size() ;
	for(i=0; i<num; i++)
		m_BarrierList[i]->Render() ;
}