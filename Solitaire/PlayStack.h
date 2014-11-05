/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : CPlayStack.h 
* Description : Header file for the PlayStack Class.
* Author :	JC Fowles
*			
* Mail :	Jc.Fowles@mediadesign.school.nz 
*
*/

#pragma once

#if !defined(__PLAYSTACK_H__)
#define __PLAYSTACK_H__

// Library Includes
#include "windows.h"

// Local Includes
#include "Card.h"
#include "Utilities.h"
//#include "Entity.h"

class CPlayStack 
{
	// Member Functions
public:
	CPlayStack(void);
	~CPlayStack(void);

	/*virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);*/

	bool AddCards(vector<CCard*>* _pCards);
	vector<CCard*>* RemoveCards(int _iCardFromTop);
	
	bool FlipCard();
	

private:
	// Disallowing copies
	CPlayStack(const CPlayStack& _kr);
	CPlayStack& operator= (const CPlayStack& _kr);
	
	bool CardCheckSuit(const CCard* const _kpCard);
	bool CardCheckValue(const CCard* const _kpCard);
	bool BlankCheck(const CCard* const _kpCard);

	// Member Variables
protected:
	vector<CCard*>*  m_pCards;
	bool m_bIsEmpty;
};

#endif //__PLAYSTACK_H__

