#ifndef BASE_ELEMENT_H
#define BASE_ELEMENT_H

enum ELEMENT
{
	NO_ELEMENT,//use this for non-interactable blocks
    //primary elements
	FIRE,
	EARTH,
	WATER,
    //secondary elements
    FIRE_2,
    WATER_2,
    EARTH_2,
    //combined elements
    SAND,// Fire + Earth
    STEAM,//Water + Fire
    WOOD,//Water+ Earth

	TOTAL_ELEMENTS,
};
enum ATTACK_TYPE
{
    NO_TYPE,//use this for non-interactable blocks
    MELEE,
    RANGED,
    ABILITY,
    TOTAL_TYPE,
};

class BaseElement
{
public:
	virtual ~BaseElement();

protected:

	ELEMENT m_CurrElement;
    ATTACK_TYPE m_CurrType;
	BaseElement(ELEMENT m_CurrElement = NO_ELEMENT, ATTACK_TYPE m_CurrType = NO_TYPE);

};

#endif // !BASE_ELEMENT_H
