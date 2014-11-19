#include "Barrier.h"

CBarrier::CBarrier() : m_pBarrierArea(0),
					   m_nBarrierAreaNum(0)
{
}
CBarrier::~CBarrier()
{
}

const POSITION* CBarrier::GetBarrierArea() const
{
	return m_pBarrierArea ;
}

const int CBarrier::GetBarrierAreaNum() const
{
	return m_nBarrierAreaNum ;
}