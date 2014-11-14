#pragma once

#include "Singleton.h"
#include <vector>

class CLineEffect ;

class CLineEffectManager : public Singleton<CLineEffectManager>
{
private :
	std::vector<CLineEffect*> m_LineEffectList ;
	const int m_nMaxLineEffect ;

public :
	CLineEffectManager() ;
	~CLineEffectManager() ;

	void Update() ;

	void Render() ;

	void Clear() ;
private :
	void Create() ;
	void Delete(int index) ;
} ;

#define g_LineEffectManager CLineEffectManager::GetInstance()