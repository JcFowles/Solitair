
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
	m_pCards = new vector<CCard*>;
	m_bIsFull = false;
}

/***********************
* ~CWinStack: Destructor for the WinStack class
* @author: Jc Fowles
********************/
CWinStack::~CWinStack(void)
{
}

/***********************
* Initialise: Initialises the PlayStack with a blank card to start with
* @author: Jc Fowles
* @parameter: _fX : x position of the playStack
* @parameter: _fY : y position of the playStack
* @return: void
********************/
bool CWinStack::Initialise(float _fX, float _fY)
{
	CCard* pBlank = new CCard;
	
	pBlank->SetFlipped(true);
	VALIDATE(pBlank->Initialise(SUIT_DEFAULT, ACE));
	pBlank->SetX(_fX);
	pBlank->SetY(_fY);
		
	m_pCards->push_back(pBlank);

	return (true);

}

/***********************
* Draw: Draws all the cards in the stack
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
void CWinStack::Draw()
{
	
	/*if(m_pCards->size() > 1)
	{
		for(unsigned int i = 1; i < m_pCards->size() ; i++)
		{
			(*m_pCards)[i]->SetX((*m_pCards)[i-1]->GetX());
			
			if((*m_pCards)[i - 1]->IsFlipped())
			{
				(*m_pCards)[i]->SetY( ((*m_pCards)[i-1]->GetY()) + 40);
			}
			else
			{
				(*m_pCards)[i]->SetY( ((*m_pCards)[i-1]->GetY()) + 10);
			}
			
			(*m_pCards)[i]->Draw();
		}
	}
	else*/
	//{
		(*m_pCards)[m_pCards->size() - 1]->Draw();
	//}
	
}

/***********************
* Process: Process the card stack
* @author: Jc Fowles
* @parameter: _fDeltaTick: How long it takes to do the procces
* @return: void
********************/
void CWinStack::Process(float _fDeltaTick)
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
	
	ECardNum eThisCardNum = _kpCard->GetNumber();
	ECardNum eBackCardNum = ((*m_pCards).back()->GetNumber());

	int iThisCardNum = static_cast<int>(eThisCardNum);
	int iBackCardNum = static_cast<int>(eBackCardNum);
	
	if( iThisCardNum == (iBackCardNum + 1) )
	{
		return true;
	}
	return false;
}

/***********************
* GetCards: Returns a pointer to the cards in the winstack
* @author: Jc Fowles
* @return: vector<CCard*>* : pointer to the cards in the winStack
********************/
vector<CCard*>* CWinStack::GetCards()
{
	return m_pCards;
}