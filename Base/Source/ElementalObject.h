#ifndef ELEMENTAL_OBJECT_H
#define ELEMENTAL_OBJECT_H

#include "GameObject.h"
#include "BaseElement.h"

class ElementalObject : public GameObject
{
public:
	virtual ~ElementalObject();
    virtual void SetElement(ELEMENT SetElement);
    virtual ELEMENT GetElement();

    virtual void Update(double dt)
    {}


protected:

	ElementalObject();
	ELEMENT m_CurrElement;



};


#endif // !ELEMENTAL_OBJECT_H
