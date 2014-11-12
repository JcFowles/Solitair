
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
	while(!(m_pCards->empty()))
	{
		delete m_pCards->back();
		m_pCards->back() = 0;
		m_pCards->pop_back();
	}

	delete m_pCards;
	m_pCards = 0;
}

/***********************
* Initialise: Initialises the PlayStack with a blank card to start with
* @author: Jc Fowles
* @parameter: _fX : x position of the playStack
* @parameter: _fY : y position of the playStack
* @return: bool: true if successful 
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
	//Only Draws the top card in the win stack
	(m_pCards)->back()->SetX((*m_pCards)[0]->GetX());
	(m_pCards)->back()->SetY( ((*m_pCards)[0]->GetY()));
	(m_pCards)->back()->Draw();
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
* AddCard: Adds a single card to the card win stack
* @author: Jc Fowles
* @parameter: _pCards: the card to add to the stack
* @return: bool : True if card was added, False if not
********************/
bool CWinStack::AddCard(CCard* _pCards)
{
	//If its only the blank card on the Winstack
	if( ((*m_pCards).back()->GetSuit()) == SUIT_DEFAULT)
	{
		//check if the card being added is an Ace
		if(_pCards->GetNumber() == ACE)
		{
			m_pCards->push_back(_pCards);
			return true;
		}
	}
	else if(CardCheckSuit(_pCards) )  //if there is any actual card on the Winstack, check the card value
	{
		m_pCards->push_back(_pCards);
		return true;
	}
	//Card could not be added
	return (false);
}

/***********************
* RemoveCard: Removes a card from the win stack
* @author: Jc Fowles
* @return: CCard* : pointer to the card removed
********************/
CCard* CWinStack::RemoveCard()
{
	CCard* returnCard = m_pCards->back();
	m_pCards->pop_back(); // remove one card from the win stack
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
	//checks if the current suit is the same as th ecard on the win stack
	if( (_kpCard->GetSuit()) == ((*m_pCards).back()->GetSuit()) )
	{
		//checks the card value
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
	//converts enums to ints
	ECardNum eThisCardNum = _kpCard->GetNumber();
	ECardNum eBackCardNum = ((*m_pCards).back()->GetNumber());
	int iThisCardNum = static_cast<int>(eThisCardNum);
	int iBackCardNum = static_cast<int>(eBackCardNum);
	
	//Checks if the value of current card is one greater than card on the Winstack already
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

/***********************
* Complete: Checks if the win stack is complete
* @author: Jc Fowles
* @return: bool : pointer to the cards in the winStack
********************/
bool CWinStack::Complete()
{
	if(m_pCards->back()->GetNumber() == KING)
	{
		return true;
	}
	
	return (false);
}