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
#include "PlayStack.h"

/***********************
* CPlayStack: Contructor for the PlayStack class
* @author: Jc Fowles
********************/
CPlayStack::CPlayStack(void)
{
	
}

/***********************
* ~CPlayStack: Destructor for the PlayStack class
* @author: Jc Fowles
********************/
CPlayStack::~CPlayStack(void)
{

}

bool CPlayStack::Initialise(float _iX, float _iY)
{
	CCard* pBlank = new CCard;
	pBlank->SetFlipped(true);
	VALIDATE(pBlank->Initialise(SUIT_DEFAULT, NUM_DEFAULT));
	CEntity::SetX(_iX);
	CEntity::SetY(_iY);

	return (true);

}

void CPlayStack::Draw()
{

}

void CPlayStack::Process(float _fDeltaTick)
{
	FlipCard();
}

/***********************
* AddCards: Adds cards to the card play stack
* @author: Jc Fowles
* @parameter: _pCards: Vector of cards to add to the stack
* @return: bool : True if cards were added, False if not
********************/
bool CPlayStack::AddCards(vector<CCard*>* _pCards)
{
	if( (CardCheckSuit((*_pCards)[0])) ||
		(BlankCheck((*_pCards)[0]))     )
	{
		for(unsigned int i = 0 ; i < _pCards->size() ; i++)
		{
			m_pCards->push_back((*_pCards)[i]);
		}
		return true;
	}
	else 
	{
		return false;
	}
}

/***********************
* RemoveCards: Remove cards to the card play stack
* @author: Jc Fowles
* @parameter: _pCards: Vector of cards to remove from the stack
* @return: bool : True if cards were removed, False if not
********************/
vector<CCard*>* CPlayStack::RemoveCards(int _iCardFromTop)
{
	vector<CCard*>* pCardsToRemove = 0;

	for(unsigned int i = _iCardFromTop; i < m_pCards->size() ; i++)
	{
		pCardsToRemove->push_back((*m_pCards)[i]);
	}

	//remove from the play stack
	for(int i = m_pCards->size(); i > _iCardFromTop; i--)
	{
		m_pCards->pop_back();
	}

	return pCardsToRemove;
}

/***********************
* CardCheck: Checks if cards can be added to stack, based on if its a red card on black or vice versa
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CPlayStack::CardCheckSuit( CCard*  _kpCard)
{
	
	if( ((_kpCard->GetSuit()) < 2) &&
		((*m_pCards).back()->GetSuit() > 1) )
	{
		return CardCheckValue(_kpCard);
	}
	else if( ((_kpCard->GetSuit()) > 1) &&
			 ((*m_pCards).back()->GetSuit() < 2) )
	{
		return CardCheckValue(_kpCard);
	}
	else
	{
		return false;
	}

}

/***********************
* FlipCard: Flips the top card if it is not visible
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if card has been flipped, False if not
********************/
bool CPlayStack::FlipCard()
{
	if(!((*m_pCards).back()->IsFlipped()))
	{
		(*m_pCards).back()->SetFlipped(true);
	}
	
	return true;

}

/***********************
* CardCheckValue: Checks if cards can be added to stack, based on its value
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CPlayStack::CardCheckValue( CCard*  _kpCard)
{
	if( (_kpCard->GetNumber()) == (((*m_pCards).back()->GetNumber()) - 1) )
	{
		return true;
	}
	return false;
}

/***********************
* BlackCheck: Checks if cards can be added to stack, based on its value
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CPlayStack::BlankCheck( CCard*  _kpCard)
{
	if( ((_kpCard->GetNumber()) == KING ) &&
		(((*m_pCards).back()->GetNumber()) == NUM_DEFAULT))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPlayStack::setStack(vector<CCard*>* _InitialStack)
{
	m_pCards = _InitialStack;
}

vector<CCard*>* CPlayStack::getStack()
{
	return m_pCards;
}