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


bool CDeck::Deal()
{
}

bool CDeck::Flip(int _num)
{
	for(int i = 1; i < _num ; i++)
	{

	}
}

bool CDeck::Reset()
{
}

CCard* CDeck::Remove()
{
}