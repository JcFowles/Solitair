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
	m_pDeck = 0;
	m_pPickUp = 0;
}

/***********************
* ~CPlayStack: Destructor for the PlayStack class
* @author: Jc Fowles
********************/
CDeck::~CDeck(void)
{

}

bool CDeck::Shuffle()
{
	random_shuffle ( (*m_pDeck).begin(), (*m_pDeck).end() );
	return true;
}

/***********************
* Initialise: Intialise the Deck with the 52 cards
* @author: Callan Moore
* @return: bool : Returns true if everything is initialise correctly
********************/
bool CDeck::Initialise()
{
	CCard* pCardTemp = 0;
	for( int i = HEART; i != SPADE; i++)	// Cycle through the suits
	{
		for( int j = ACE; j != KING; j++)	// Cycle through the 13 card values
		{
			pCardTemp = new CCard;
			VALIDATE(pCardTemp->Initialise(static_cast<ESuit>(i), static_cast<ECardNum>(j)));
			m_pDeck->push_back(pCardTemp);
		}
	}
	return true;
}

bool CDeck::Deal()
{
	return true;
}

bool CDeck::Flip(int _num)
{
	for(int i = 1; i < _num ; i++)
	{

	}
	return true;
}

bool CDeck::Reset()
{
	return true;
}

CCard* CDeck::Remove()
{
	return 0;
}