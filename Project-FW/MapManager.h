#pragma once

#include "Singleton.h"
#include <vector>

class CBarrier ;
class CPlanet ;

class CMapManager : public Singleton<CMapManager>
{
private :
	int m_nMap[9][9], m_nMapBarrier[9][9] ;
	int m_nMapNumber ;
	int m_nMapSize ;
	float m_fMapStartXY[3][2] ;
	float m_fMapSpace[3] ;
	std::vector<CPlanet*> m_PlanetList ;
	std::vector<CBarrier*> m_BarrierList ;

public :
	CMapManager() ;
	~CMapManager() ;

	void SetMapNumber(int num) ;
	bool SetBarrier(CBarrier *pBarrier, int IndexX, int IndexY) ;
	bool BuildBarrier(int Type, float IndexPosX, float IndexPosY) ;

	const int GetMapSize() const ;
	const int GetMapNumber() const ;
	const bool InMapArea(float x, float y, float &IndexPosX, float &IndexPosY) const ;

	void LoadMapData() ;

	void ClearMap() ;

	void Update() ;

	void Render() ;
} ;

#define g_MapManager CMapManager::GetInstance()