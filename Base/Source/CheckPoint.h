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

private:
	LEVEL m_RespawnLevel;
	Vector3 m_RespawnOffset;
};


#endif // !_CHECKPOINT_H
