#ifndef LEVEL_H
#define	LEVEL_H

#include "Vector3.h"

//enum LEVEL
//{
//	TEST,
//	TUTORIAL,
//	LEVEL_1,
//	LEVEL_2,
//	LEVEL_3,
//	LEVEL_4,
//};

class Level
{
private:
	Vector3 m_StartPos;
	Vector3 m_OrigCamPos;
	Vector3 m_OrigCamTarget;

	//LEVEL m_CurrLevel;

public:
	Level();
	~Level();

	void InitLevel(Vector3 StartPos, Vector3 OrigCamPos = Vector3(0, 0, 1), Vector3 OrigCamTarget = Vector3(0, 0, 0));

	Vector3 GetStartPos();
	Vector3 GetOrigCamPos();
	Vector3 GetOrigCamTarget();
};

#endif // !LEVEL_H
