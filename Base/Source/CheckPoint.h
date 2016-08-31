#ifndef _CHECKPOINT_H
#define _CHECKPOINT_H

#include "Environment.h"

class Checkpoint : public Environment
{
public:
	Checkpoint();
	~Checkpoint();

	void SetCheckpoint(LEVEL CurrLevel, Vector3 MapOffset);

	LEVEL GetLevel();
	Vector3 GetMapOffset();

	bool GetCheckpointActive();

private:
	LEVEL m_RespawnLevel;
	Vector3 m_RespawnOffset;
	bool m_CheckpointActive;
};


#endif // !_CHECKPOINT_H
