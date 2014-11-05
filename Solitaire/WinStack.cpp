
/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : CPlayStack.cpp
* Description : Implementation file for the PlayStack class
* Author :	JC Fowles

* Mail :	Jc.fowles@mediadesign.school.nz		
*/

// This include
#include "WinStack.h"

/***********************
* CWinStack: Contructor for the WinStack class
* @author: Jc Fowles
********************/
CWinStack::CWinStack(void)
{
}

/***********************
* ~CWinStack: Destructor for the WinStack class
* @author: Jc Fowles
********************/
CWinStack::~CWinStack(void)
{
}


/***********************
* AddCard: Adds a cards to the card win stack
* @author: Jc Fowles
* @parameter: _pCards: the card to add to the stack
* @return: bool : True if card was added, False if not
********************/
bool CWinStack::AddCard(CCard* _pCards)
{
	if( CardCheckSuit(_pCards) ||
	((*m_pCards).back()->GetSuit()) == SUIT_DEFAULT)
	{
		m_pCards->push_back(_pCards);
		return true;
	}
	else 
	{
		return false;
	}
}

/***********************
* RemoveCard: Removes a card from the win stack
* @author: Jc Fowles
* @return: CCard* : pointer to the card removed
********************/
CCard* CWinStack::RemoveCard()
{
	CCard* returnCard = m_pCards->back();
	m_pCards->pop_back(); // remove from the win stack
	return returnCard;
}

/***********************
* CardCheck: Checks if cards can be added to stack, based on if its a red card on black or vice versa
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CWinStack::CardCheckSuit( CCard*  _kpCard)
{
	
	if( (_kpCard->GetSuit()) == ((*m_pCards).back()->GetSuit()) )
	{
		return CardCheckValue(_kpCard);
	}
	else
	{
		return false;
	}

}

/***********************
* CardCheckValue: Checks if cards can be added to stack, based on its value
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CWinStack::CardCheckValue( CCard* _kpCard)
{
	if( (_kpCard->GetNumber()) == (((*m_pCards).back()->GetNumber()) - 1) )
	{
		return true;
	}
	return false;
}