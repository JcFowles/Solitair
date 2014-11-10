/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : CDeck.cpp
* Description : Implementation file for the Deck class
* Author :	JC Fowles

* Mail :	Jc.fowles@mediadesign.school.nz		
*/

// This include
#include "Deck.h"

/***********************
* CPlayStack: Contructor for the PlayStack class
* @author: Jc Fowles
********************/
CDeck::CDeck(void)
{
	m_pDraw = new deque<CCard*>;
	m_pPickUp = new deque<CCard*>;
	m_NumFlip = 3;
}

/***********************
* ~CPlayStack: Destructor for the PlayStack class
* @author: Jc Fowles
********************/
CDeck::~CDeck(void)
{
	
	while(!m_pDraw->empty())
	{
		m_pDraw->pop_back();
	}
	delete m_pDraw;
	m_pDraw = 0;

	while(!m_pPickUp->empty())
	{
		m_pPickUp->pop_back();
	}
	delete m_pPickUp;
	m_pPickUp = 0;
}

/***********************
* Initialise: Intialise the Deck with the 52 cards
* @author: Callan Moore
* @author: Jc Fowles
* @parameter: _fX : x position of the playStack
* @parameter: _fY : y position of the playStack
* @parameter: _pThePlayStacks : pointer all 7 PlayStacks
* @return: bool : return true if it worked
********************/
bool CDeck::Initialise(float _iX, float _iY, vector<CPlayStack*>* _pThePlayStacks)
{
	theBackCard = new CCard;
	VALIDATE(theBackCard->Initialise(SUIT_DEFAULT, THREE));
	theBackCard->SetX(_iX);
	theBackCard->SetY(_iY);
	


	CCard* pCardTemp = 0;
	for( int i = HEART; i != SUIT_DEFAULT; i++)	// Cycle through the suits
	{
		for( int j = ACE; j != KING+1; j++)	// Cycle through the 13 card values
		{
			pCardTemp = new CCard;

			VALIDATE(pCardTemp->Initialise(static_cast<ESuit>(i), static_cast<ECardNum>(j)));
			pCardTemp->SetX(theBackCard->GetX());
			pCardTemp->SetY(theBackCard->GetY());
			m_pDraw->push_back(pCardTemp);
		}
	}

	//CEntity::SetX(_iX);
	//CEntity::SetY(_iY);

	Shuffle();
	theBackCard->SetFlipped(true);
	m_pDraw->push_front(theBackCard);
	Deal(_pThePlayStacks);
	return true;
}

/***********************
* Draw: Draws all the cards in the Deck, both the deck itself and pick Up pile
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
void CDeck::Draw()
{
	if(m_pDraw->empty())
	{
		theBackCard->Draw();
	}
	else
	{
		m_pDraw->back()->Draw();
	}

	int iPickUpSize = m_pPickUp->size() ;

	if(iPickUpSize > 0)
	{
		int flip = m_NumFlip;
		if(iPickUpSize < m_NumFlip)
		{
			flip = iPickUpSize;
		}
		for(int k = 0; k < flip; k++)
		{
			(*m_pPickUp)[iPickUpSize - 1 - k ]->SetX(260.0f + k*30.0f);
		}

		for(int i = 0 ; i < iPickUpSize  ; i++)
		{
			(*m_pPickUp)[i]->Draw();
		}

		for(int k = 0; k < flip; k++)
		{
			(*m_pPickUp)[iPickUpSize - 1 - k ]->SetX(260.0f );
		}
	}

}

/***********************
* Process: Process the Deck
* @author: Jc Fowles
* @parameter: _fDeltaTick: How long it takes to do the procces
* @return: void
********************/
void CDeck::Process(float _fDeltaTick)
{

}

/***********************
* Shuffle: Shuffles the Deck
* @author: Jc Fowles
* @return: bool: always return true;
********************/
bool CDeck::Shuffle()
{
	random_shuffle ( (*m_pDraw).begin(), (*m_pDraw).end() );
	return true;
}

/***********************
* Deal: Deals out the cards from the Deck, to the play stacks
* @author: Jc Fowles
* @return: bool: always return true;
********************/
bool CDeck::Deal(vector<CPlayStack*>* _pThePlayStack)
{
	vector<CCard*>* tempCardStack ;
	for(int i = 0 ; i < 7 ; i++)
	{
		
		tempCardStack = (*_pThePlayStack)[i]->GetStack();

		for(int k = 0; k <= i; k++)
		{
			tempCardStack->push_back(m_pDraw->back());
			m_pDraw->pop_back();
			//tempCardStack->back()->SetY()
		}
		tempCardStack->back()->SetFlipped(true);
	}
	return true;
}

/***********************
* Flip: Flip the top number of cards, based on the passed in value
* @author: Jc Fowles
* @return: bool: always return true;
********************/
bool CDeck::Flip()
{
	/*if(m_NumFlip > 1)
	{*/
	for(int i = 0; i < m_NumFlip ; i++)
	{
		if((*m_pDraw->back()).GetSuit() ==  SUIT_DEFAULT )
		{
			Reset();
			break;
		}
		else
		{
			m_pPickUp->push_back(m_pDraw->back());
			m_pDraw->pop_back();
			m_pPickUp->back()->SetFlipped(true);
			m_pPickUp->back()->SetX((260.0f)); // + i*30.0f);
		}
	}

	return true;
}

/***********************
* Reset: Resets The cards in the pick up pile back to the deck in the correct order
* @author: Jc Fowles
* @return: bool: always return true;
********************/
bool CDeck::Reset()
{
	//for(unsigned int i = 0; i < m_pPickUp->size() ; i++)
	while(!(m_pPickUp->empty()))
	{
		
		m_pPickUp->back()->SetFlipped(false);
		m_pPickUp->back()->SetX(m_pDraw->front()->GetX());
		m_pDraw->push_back(m_pPickUp->back());
		m_pPickUp->pop_back();
		
	}

	

	return true;
}

/***********************
* Remove: Returns and Removes the top card of the pick up pile
* @author: Jc Fowles
* @return: vector<CCard*>*: The top card;
********************/
vector<CCard*>* CDeck::Remove()
{
	vector<CCard*>* pThisCard = 0;
	pThisCard->push_back(m_pPickUp->back());
	m_pPickUp->pop_back();

	return pThisCard;
}

/***********************
* GetDrawPile: Returns the Draw pile
* @author: Jc Fowles
* @return: deque<CCard*>*: pointer to the draw pile
********************/
deque<CCard*>* CDeck::GetDrawPile()
{
	return m_pDraw;
}

/***********************
* GetPickUpPile: Returns the pickUp pile
* @author: Jc Fowles
* @return: deque<CCard*>*: pointer to the pickUP pile
********************/
deque<CCard*>* CDeck::GetPickUpPile()
{
	return m_pPickUp;
}

/***********************
* setFlipNum: sets the number of cards to flip
* @author: Jc Fowles
* @parameter: _num : The number of cards to flip
* @return: deque<CCard*>*: pointer to the pickUP pile
********************/
void CDeck::setFlipNum(int _iNum)
{
	m_NumFlip = _iNum;
}