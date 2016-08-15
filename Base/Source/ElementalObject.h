#ifndef ELEMENTAL_OBJECT_H
#define ELEMENTAL_OBJECT_H

#include "GameObject.h"
#include "BaseElement.h"

class ElementalObject : public GameObject
{
public:
	virtual ~ElementalObject();

protected:

	ElementalObject();

	ELEMENT m_CurrElement;
    ATTACK_TYPE m_CurrAttackType;

	virtual ELEMENT GetElement();
    virtual ATTACK_TYPE GetAttackType();
	virtual void SetElement(ELEMENT SetElement);
    virtual void SetAttackType(ATTACK_TYPE SetAttackType);
};


#endif // !ELEMENTAL_OBJECT_H
