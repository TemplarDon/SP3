#ifndef BASE_ELEMENT_H
#define BASE_ELEMENT_H

enum ELEMENT
{
	NONE,
	FIRE,
	EARTH,
	WATER,
	AIR,
	TOTAL_ELEMENTS,
};

class BaseElement
{
public:
	virtual ~BaseElement();

protected:

	ELEMENT m_CurrElement;

	BaseElement(ELEMENT m_CurrElement = NONE);

	virtual void Attack();
	virtual void Ability();
};

#endif // !BASE_ELEMENT_H
