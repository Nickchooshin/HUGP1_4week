#include "StageManager.h"
#include <stdio.h>

CStageManager::CStageManager() : m_nOpenStageNum(0)
{
}
CStageManager::~CStageManager()
{
}

const int CStageManager::GetOpenStageNum() const
{
	return m_nOpenStageNum ;
}

void CStageManager::LoadStageDat()
{
	FILE *StageDat ;

	StageDat = fopen("Resource/Data/Stage.dat", "rb") ;
	if(StageDat==NULL)
	{
		SaveStageDat() ;

		StageDat = fopen("Resource/Data/Stage.dat", "rb") ;
	}

	fscanf(StageDat, "%d", &m_nOpenStageNum) ;

	fclose(StageDat) ;
}

void CStageManager::SaveStageDat()
{
	FILE *StageDat ;

	StageDat = fopen("Resource/Data/Stage.dat", "wb") ;

	fprintf(StageDat, "%d", m_nOpenStageNum) ;

	fclose(StageDat) ;
}

void CStageManager::OpenStage(int StageNum)
{
	if(StageNum>m_nOpenStageNum)
		m_nOpenStageNum = StageNum ;
}