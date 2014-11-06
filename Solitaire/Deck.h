/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : CDeck.h 
* Description : Header file for the Deck Class.
* Author :	JC Fowles
*			
* Mail :	Jc.Fowles@mediadesign.school.nz 
*
*/

#pragma once

#if !defined(__DECK_H__)
#define __DECK_H__

// Local Includes
#include "PlayStack.h"

// Prototypes
class CCard;
class CPlayStack;
class CDeck : public CEntity
{
public:
	// Member Functions
	CDeck(void);
	~CDeck(void);

	
	virtual bool Initialise(float _iX, float _iY, vector<CPlayStack*>* _pThePlayStacks);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	bool Shuffle();
	bool Deal(vector<CPlayStack*>* _pThePlayStack);

	bool Flip(int _num);
	bool Reset();

	vector<CCard*>* Remove();

	// Member Variables
protected:
	deque<CCard*>* m_pDeck;
	deque<CCard*>* m_pPickUp;

	CCard* theBackCard;
};

#endif //__DECK_H__
