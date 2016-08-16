#ifndef ELEMENTAL_OBJECT_H
#define ELEMENTAL_OBJECT_H

#include "GameObject.h"
#include "BaseElement.h"

class ElementalObject : public GameObject
{
public:
	virtual ~ElementalObject();
    virtual void SetElement(ELEMENT SetElement);

protected:

	ElementalObject();
	ELEMENT m_CurrElement;
	virtual ELEMENT GetElement();


};


#endif // !ELEMENTAL_OBJECT_H
