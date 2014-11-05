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

// Library Includes
#include "windows.h"

// Local Includes
#include "Card.h"
#include "Utilities.h"
//#include "Entity.h"

class CDeck
{
public:
	CDeck(void);
	~CDeck(void);

	bool Shuffle();
	bool Deal();

	bool Flip(int _num);
	bool Reset();

	CCard* Remove();

protected:
	vector<CCard*>* m_pDeck;
	vector<CCard*>* m_pPickUp;
};

#endif //__DECK_H__
