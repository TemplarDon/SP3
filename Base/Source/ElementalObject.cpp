#include "ElementalObject.h"

ElementalObject::ElementalObject()
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