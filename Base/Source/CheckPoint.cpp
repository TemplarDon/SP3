#include "CheckPoint.h"

Checkpoint::Checkpoint()
{
}

Checkpoint::~Checkpoint()
{
}

void Checkpoint::SetCheckpoint(LEVEL CurrLevel, Vector3 MapOffset)
{
	m_RespawnLevel = CurrLevel;
	m_RespawnOffset = MapOffset;
}

LEVEL Checkpoint::GetLevel()
{
	return m_RespawnLevel;
}

Vector3 Checkpoint::GetMapOffset()
{
	return m_RespawnOffset;
}