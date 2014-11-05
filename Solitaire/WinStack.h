/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : CWinStack.h 
* Description : Header file for the WinStack Class.
* Author :	JC Fowles
*			
* Mail :	Jc.Fowles@mediadesign.school.nz 
*
*/

#pragma once

#if !defined(__WINSTACK_H__)
#define __WINSTACK_H__

// Library Includes
#include "windows.h"

// Local Includes
#include "Card.h"
#include "Utilities.h"
//#include "Entity.h"


class CWinStack
{
	//Member Functions
public:
	CWinStack(void);
	~CWinStack(void);

	bool AddCard(CCard*_pCards);
	CCard* RemoveCard();


private:
	// Disallowing copies
	CWinStack(const CWinStack& _kr);
	CWinStack& operator= (const CWinStack& _kr);
	
	bool CardCheckSuit(const CCard* const _kpCard);
	bool CardCheckValue(const CCard* const _kpCard);

	// Member Variables
protected:
	vector<CCard*>* m_pCards;
	bool m_bIsFull;
};

#endif
