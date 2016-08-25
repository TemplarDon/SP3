#include "ElementalObject.h"

ElementalObject::ElementalObject()
: m_CurrElement(NO_ELEMENT)
{
}

ElementalObject::~ElementalObject()
{
}

ELEMENT ElementalObject::GetElement()
{
	
	return m_CurrElement;
}

void ElementalObject::SetElement(ELEMENT SetElement)
{
	m_CurrElement = SetElement;
}




