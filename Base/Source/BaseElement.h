#ifndef BASE_ELEMENT_H
#define BASE_ELEMENT_H

enum ELEMENT
{
	NO_ELEMENT,//use this for non-interactable blocks
	MISC,
    EATING,//nom nom nom
    //primary elements
	FIRE, //1
	EARTH, //2
	WATER, //3
    //secondary elements
    FIRE_2,
    WATER_2,
    EARTH_2,	
	TOTAL_ELEMENTS,
};

class BaseElement
{
public:
	virtual ~BaseElement();

protected:

	ELEMENT m_CurrElement;
	BaseElement(ELEMENT m_CurrElement = NO_ELEMENT);

};

#endif // !BASE_ELEMENT_H
