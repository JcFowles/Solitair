/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : CWinStack.h 
* Description : Header file for the WinStack Class.
* Author :	JC Fowles		
* Mail :	Jc.Fowles@mediadesign.school.nz 
*/

#pragma once

#if !defined(__WINSTACK_H__)
#define __WINSTACK_H__

// Local Includes
#include "Card.h"

class CWinStack : public CEntity
{
	//Member Functions
public:
	CWinStack(void);
	~CWinStack(void);

	virtual bool Initialise(float _fX, float _fY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	bool AddCard(CCard*_pCards);
	CCard* RemoveCard();
	bool Complete();

	//Getter
	vector<CCard*>* GetCards();
	
private:
	// Disallowing copies
	CWinStack(const CWinStack& _kr);
	CWinStack& operator= (const CWinStack& _kr);
	
	bool CardCheckSuit( CCard*  _kpCard);
	bool CardCheckValue( CCard*  _kpCard);

	// Member Variables
protected:
	vector<CCard*>* m_pCards;
	bool m_bIsFull;
};

#endif
