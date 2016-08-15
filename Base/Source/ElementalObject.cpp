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

ATTACK_TYPE ElementalObject::GetAttackType()
{
    return m_CurrAttackType;
}
void ElementalObject::SetAttackType(ATTACK_TYPE SetAttackType)
{
    m_CurrAttackType = SetAttackType;
}
