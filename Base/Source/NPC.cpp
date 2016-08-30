#include "NPC.h"

NPC::NPC()
{}

NPC::~NPC()
{}

void NPC::InitNPC(bool InteractableStatus)
{
	m_Interactable = InteractableStatus;
	m_ShowText = false;
}

void NPC::SetDialouge(string Dialouge)
{
	m_DialougeVec.push_back(Dialouge);
}

std::vector<std::string> NPC::GetDialougeVec()
{
	return m_DialougeVec;
}

void NPC::SetShowText(bool status)
{
	m_ShowText = status;
}

bool NPC::GetShowText()
{
	return m_ShowText;
}

void NPC::SetInteractable(bool status)
{
	m_Interactable = status;
}

bool NPC::GetInteractable()
{
	return m_Interactable;
}

void NPC::CollisionResponse(GameObject* OtherGo)
{

}