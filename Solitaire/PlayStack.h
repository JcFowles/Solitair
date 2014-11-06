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


class CCard;
class CPlayStack : public CEntity
{
	// Member Functions
public:
	CPlayStack(void);
	~CPlayStack(void);

	virtual bool Initialise(float _iX, float _iY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	bool AddCards(vector<CCard*>* _pCards);
	vector<CCard*>* RemoveCards(int _iCardFromTop);
	
	bool FlipCard();
	
	void SetStack(vector<CCard*>* _InitialStack);
	vector<CCard*>* GetStack();

private:
	// Disallowing copies
	CPlayStack(const CPlayStack& _kr);
	CPlayStack& operator= (const CPlayStack& _kr);
	


	bool CardCheckSuit( CCard*  _kpCard);
	bool CardCheckValue( CCard*  _kpCard);
	bool BlankCheck( CCard*  _kpCard);

	// Member Variables
protected:
	vector<CCard*>*  m_pCards;
	bool m_bIsFlipped;
};

#endif //__PLAYSTACK_H__

