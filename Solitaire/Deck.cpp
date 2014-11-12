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
	//I want a comment here
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
	//Deletes the Draw Pile
	while(!m_pDraw->empty())
	{
		delete m_pDraw->back();
		m_pDraw->back() = 0;
	
		m_pDraw->pop_back();
	}
	delete m_pDraw;
	m_pDraw = 0;

	//Deletes the Pick up Pile
	while(!m_pPickUp->empty())
	{
		delete m_pPickUp->back();
		m_pPickUp->back() = 0;
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
* @return: bool : True if Successfull
********************/
bool CDeck::Initialise(float _fX, float _fY, vector<CPlayStack*>* _pThePlayStacks)
{
	//Creates a blank card as the place holder for the Deck
	theBackCard = new CCard;
	VALIDATE(theBackCard->Initialise(SUIT_DEFAULT, THREE));
	theBackCard->SetX(_fX);
	theBackCard->SetY(_fY);
	
	//Adds cards to the Deck
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
	pCardTemp = 0;

	//Shuffles the Deck
	Shuffle();
	//Adds the blank card to the bottom of the Deck
	theBackCard->SetFlipped(true);
	m_pDraw->push_front(theBackCard);
	//Deals out cards to the play stacks
	Deal(_pThePlayStacks);

	return (true);
}

/***********************
* Draw: Draws all the cards in the Deck, both the Draw pile itself and pick Up pile
* @author: Jc Fowles
* @return: void
********************/
void CDeck::Draw()
{
	int iPickUpSize = m_pPickUp->size() ;

	//Sets the back card to a X or O depending if the deck empty or not
	if((m_pDraw->size() == 1) && 
		(iPickUpSize <= 0) )
	{
		(*m_pDraw)[0]->SetNumber(TWO);
	}
	else
	{
		(*m_pDraw)[0]->SetNumber(THREE);
	}

	//Draw the Draw pile
	m_pDraw->back()->Draw();

	
	
	//if There are cards in the pick up pile
	if(iPickUpSize > 0)
	{
		int flip = m_NumFlip;

		if(iPickUpSize < m_NumFlip)
		{
			flip = iPickUpSize;
		}
		//move flip number of cards to be able to see that many cards
		for(int k = 0; k < flip; k++)
		{
			(*m_pPickUp)[iPickUpSize - 1 - k ]->SetX(260.0f + k*30.0f);
			(*m_pPickUp)[iPickUpSize - 1 - k ]->SetY(m_pDraw->back()->GetY());
		}
		//Draw the pickUpPile
		for(int i = 0 ; i < iPickUpSize  ; i++)
		{
			(*m_pPickUp)[i]->Draw();
		}
		
		//reset the position back to the the starting point of the pick up Pile
		for(int k = 0; k < flip; k++)
		{
			(*m_pPickUp)[iPickUpSize - 1 - k ]->SetX(260.0f );
			(*m_pPickUp)[iPickUpSize - 1 - k ]->SetY(m_pDraw->back()->GetY());
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
	//resets if the only card in the draw pile is the blank card
	if((*m_pDraw->back()).GetSuit() ==  SUIT_DEFAULT )
	{
			Reset();
	}
	else
	{
		int iFlipAmount = m_NumFlip;

		if(static_cast<int>(m_pDraw->size()) < m_NumFlip)
		{
			iFlipAmount = m_pDraw->size() - 1;
		}
		
		//Add iFlipAmount amount of cards to the pick Up Pile from the Draw pile
		for(int i = 0; i < iFlipAmount ; i++)
		{
			if((m_pDraw->back()->GetSuit() != SUIT_DEFAULT))
			{
				m_pPickUp->push_back(m_pDraw->back());
				m_pDraw->pop_back();
				m_pPickUp->back()->SetFlipped(true);
				m_pPickUp->back()->SetX((260.0f)); 
			}
		}
	}

	return (true);
}

/***********************
* Reset: Resets The cards in the pick up pile back to the deck in the correct order
* @author: Jc Fowles
* @return: bool: always return true;
********************/
bool CDeck::Reset()
{
	//Adds all the cards in the Pick Up pile back to the Draw pile, in the same order
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

/***********************
* getFlipNum: Return the number of cards to flip
* @author: Jc Fowles
* @return: int: 
********************/
int CDeck::getFlipNum()
{
	return m_NumFlip;
}