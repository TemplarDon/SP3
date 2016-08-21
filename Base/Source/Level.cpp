#include "Level.h"

Level::Level()
{}

Level::~Level()
{}

void Level::InitLevel(Vector3 StartPos, Vector3 OrigCamPos, Vector3 OrigCamTarget)
{
	m_StartPos = StartPos;
	m_OrigCamPos = m_OrigCamPos;
	m_OrigCamTarget = m_OrigCamTarget;
}

Vector3 Level::GetStartPos()
{
	return m_StartPos;
}

Vector3 Level::GetOrigCamPos()
{
	return m_OrigCamPos;
}

Vector3 Level::GetOrigCamTarget()
{
	return m_OrigCamTarget;
}