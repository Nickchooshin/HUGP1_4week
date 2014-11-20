#pragma once

#include "Singleton.h"
#include <vector>

class CBarrier ;
class CPlanet ;
class CMeteor ;
class CResultUI ;

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

	bool m_bOperate, m_bResult ;
	bool m_bClear ;
	CMeteor *m_pMeteor ;
	CResultUI *m_pResultUI ;

public :
	CMapManager() ;
	~CMapManager() ;

	void SetMapNumber(int num) ;
	bool SetBarrier(CBarrier *pBarrier, int IndexX, int IndexY) ;
	bool BuildBarrier(int Type, float IndexPosX, float IndexPosY) ;
	void Operate() ;

	const int GetMapSize() const ;
	const int GetMapNumber() const ;
	const bool InMapArea(float x, float y, float &IndexPosX, float &IndexPosY) const ;

	void LoadMapData() ;
	void ClearMap() ;

	void Init() ;

	void Update() ;

	void Render() ;
	void Render_Result() ;
private :
	void DestroyPlanet() ;
} ;

#define g_MapManager CMapManager::GetInstance()