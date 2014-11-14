#include "LineEffectManager.h"
#include "LineEffect.h"

CLineEffectManager::CLineEffectManager() : m_nMaxLineEffect(20)
{
}
CLineEffectManager::~CLineEffectManager()
{
	Clear() ;
}

void CLineEffectManager::Update()
{
	int i ;
	int num = m_LineEffectList.size() ;

	for(i=0; i<num; i++)
	{
		m_LineEffectList[i]->Update() ;

		if(!m_LineEffectList[i]->IsLife())
		{
			Delete(i) ;
			--i ;
			--num ;
		}
	}

	Create() ;
}

void CLineEffectManager::Render()
{
	int i ;
	const int num = m_LineEffectList.size() ;

	for(i=0; i<num; i++)
		m_LineEffectList[i]->Render() ;
}

void CLineEffectManager::Clear()
{
	int i ;
	const int num = m_LineEffectList.size() ;

	for(i=0; i<num; i++)
		delete m_LineEffectList[i] ;

	m_LineEffectList.clear() ;
}

void CLineEffectManager::Create()
{
	int num = m_LineEffectList.size() ;

	while(num < m_nMaxLineEffect)
	{
		CLineEffect *pLineEffect ;
		pLineEffect = new CLineEffect ;
		pLineEffect->Init() ;

		m_LineEffectList.push_back(pLineEffect) ;

		++num ;
	}
}

void CLineEffectManager::Delete(int index)
{
	delete m_LineEffectList[index] ;

	m_LineEffectList.erase(m_LineEffectList.begin() + index) ;
}