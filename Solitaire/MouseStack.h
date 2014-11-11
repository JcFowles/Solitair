/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : MouseStack.h
* Description : Header file for the Mouse Stack Class
* Author :	Callan Moore
*			Nick Gould
* Mail :	Callan.Moore@mediadesign.school.nz 
*			Nick.gould@mediadesign.school.nz
*/

#pragma once

// Local Includes
#include "Card.h"

class CCard;
class CMouseStack : public CEntity
{
	// Member Functions
public:
	CMouseStack(void);
	~CMouseStack(void);
	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	vector<CCard*>* GetHeldCards();
	void SetHeldCards(vector<CCard*>* _pCards);
	void SetMousePosition(float _fMouseX, float _fMouseY);
	float GetMouseX();
	float GetMouseY();



	// Member Variables
private:
	float m_fPrevX;
	float m_fPrevY;
	vector<CCard*>* m_pHeldCards;
};

