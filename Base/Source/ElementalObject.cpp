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

ATTACK_TYPE ElementalObject::GetAttackType()
{
	return m_CurrAttackType;
}

void ElementalObject::SetElement(ELEMENT SetElement)
{
	m_CurrElement = SetElement;
}




