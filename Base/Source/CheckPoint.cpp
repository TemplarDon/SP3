#include "CheckPoint.h"

Checkpoint::Checkpoint()
	: m_CheckpointActive(false)
{
}

Checkpoint::~Checkpoint()
{
}

void Checkpoint::SetCheckpoint(LEVEL CurrLevel, Vector3 MapOffset)
{
	m_RespawnLevel = CurrLevel;
	m_RespawnOffset = MapOffset;
	m_CheckpointActive = true;
}

LEVEL Checkpoint::GetLevel()
{
	return m_RespawnLevel;
}

Vector3 Checkpoint::GetMapOffset()
{
	return m_RespawnOffset;
}

bool Checkpoint::GetCheckpointActive()
{
	return m_CheckpointActive;
}