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
	virtual ELEMENT GetElement();
	virtual void SetElement(ELEMENT SetElement);



};


#endif // !ELEMENTAL_OBJECT_H
