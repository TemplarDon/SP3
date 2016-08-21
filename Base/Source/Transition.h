#ifndef TRANSITION_H
#define TRANSITION_H

#include "Environment.h"

class Transition : public Environment
{
public:
	Transition();
	virtual ~Transition();

	void SetNextTransition(LEVEL m_NextTransition);
	LEVEL GetNextTransition();

protected:
	LEVEL m_NextTransition;
};

#endif // !TRANSITION_H
