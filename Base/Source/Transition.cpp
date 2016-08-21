#include "Transition.h"

Transition::Transition()
{}

Transition::~Transition()
{}

void Transition::SetNextTransition(LEVEL NextTransition)
{
	m_NextTransition = NextTransition;
}

LEVEL Transition::GetNextTransition()
{
	return m_NextTransition;
}