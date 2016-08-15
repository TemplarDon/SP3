#ifndef ELEMENTAL_OBJECT_H
#define ELEMENTAL_OBJECT_H

#include "GameObject.h"
#include "BaseElement.h"

enum ATTACK_TYPE
{
    NO_ATTACK_TYPE,//use this for non-interactable blocks
    MELEE,
    RANGED,
    ABILITY,
    TOTAL_ATTACK_TYPE,
};

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

private:
    virtual void SetAttackType();//a;ways corresponds to element type

};


#endif // !ELEMENTAL_OBJECT_H
