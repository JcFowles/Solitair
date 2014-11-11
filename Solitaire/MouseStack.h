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

class CPlayStack;
class CWinStack;
class CDeck;
class CCard;

class CMouseStack : public CEntity
{
	// Member Functions
public:
	CMouseStack(void);
	virtual ~CMouseStack(void);

	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	// Getters
	vector<CCard*>* GetHeldCards();
	float GetMouseX();
	float GetMouseY();
	CDeck* GetPrevDeck();
	CWinStack* GetPrevWinStack();
	CPlayStack* GetPrevPlayStack();

	// Setters
	void SetHeldCards(vector<CCard*>* _pCards);
	void SetMousePosition(float _fMouseX, float _fMouseY);
	void SetPrevDeck( CDeck* _pPrevDeck);
	void SetPrevWinStack( CWinStack* _pPrevWinStack);
	void SetPrevPlayStack( CPlayStack* _pPrevPlayStack);

	// Member Variables
private:
	float m_fPrevX;
	float m_fPrevY;
	vector<CCard*>* m_pHeldCards;
	CDeck* m_pPrevDeck;
	CWinStack* m_pPrevWinStack;
	CPlayStack* m_pPrevPlayStack;
};

