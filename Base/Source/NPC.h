#ifndef NPC_H
#define NPC_H

#include "GameObject.h"
#include "Sound.h"
#include <iostream>
#include <string>

using std::string;

class NPC : public GameObject
{

public:
	NPC();
	~NPC();

	void InitNPC(bool InteractableStatus);

	void SetDialouge(string Dialouge);
	std::vector<std::string> GetDialougeVec();

	void SetShowText(bool status);
	bool GetShowText();

	void SetInteractable(bool status);
	bool GetInteractable();

	virtual void CollisionResponse(GameObject* OtherGo);

private:
	Sound music;
	std::vector<string> m_DialougeVec;
	
	bool m_ShowText;
	bool m_Interactable;

};

#endif // !_NPC_H
