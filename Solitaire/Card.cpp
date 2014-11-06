/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Backbuffer.h
* Description : Header file for the Backbuffer class
* Author :	Callan Moore
*			JC Fowles
*			Nick Gould
* Mail :	Callan.moore@mediadesign.school.nz
*			Jc.fowles@mediadesign.school.nz	
*			Nick.gould@mediadesign.school.nz
*/

// This Include
#include "Card.h"

CCard::CCard(void)
{
	m_bFlipped = false;
	m_eSuit = SUIT_DEFAULT;
	m_eCardNum = NUM_DEFAULT;
}


CCard::~CCard(void)
{

}

/***********************
* Initialise: Initialises the entity and creates its sprite (image)
* @author: Nick Gould
* @author: Callan Moore
* @parameter:_ESuit: the enumerator card suit
* @parameter:_ECardnum: the enumerator card number
* @return: bool: always returns true
********************/
bool CCard::Initialise(ESuit _ESuit, ECardNum _ECardnum)
{
	m_iMaskID = IDB_MASK_CARD;
	m_iSpriteID_Y = _ESuit;
	m_iSpriteID_X = _ECardnum;
	return true;
}

/***********************
* Draw: Calls the entity's sprite's draw function.
* @author: Nick Gould
* @return: void
********************/
void CCard::Draw()
{

}

/***********************
* Process: Process the changes to the card for the current Delta Tick
* @author: Nick Gould
* @parameter: _fDeltaTick
* @return: void
********************/
void CCard::Process(float _fDeltaTick)
{

}

/***********************
* GetSuit: Gives the enum associated with the card suit
* @author: Nick Gould
* @return: ESuit: the card's suit
********************/
ESuit CCard::GetSuit()
{
	return m_eSuit;
}


/***********************
* GetNumber: Gives the enum associated with the card number
* @author: Nick Gould
* @return: ECardNum: the card's number
********************/
ECardNum CCard::GetNumber()
{
	return m_eCardNum;
}

/***********************
* IsVisible: Shows 
* @author: Nick Gould
* @return: bool
********************/
bool CCard::IsFlipped()
{
	return m_bFlipped; 
}

/***********************
* SetSuit: Sets the suit of the card
* @author: Nick Gould
* @parameter: _fDeltaTick
* @return: void
********************/
void CCard::SetSuit(ESuit _eSuit)
{
	_eSuit = m_eSuit;
}

/***********************
* SetNumber: Sets the number of the card
* @author: Nick Gould
* @parameter: _eCardNum
* @return: void
********************/
void CCard::SetNumber(ECardNum _eCardNum)
{
	_eCardNum = m_eCardNum;
}

/***********************
* SetVisible: Sets whether the card is visible or not.
* @author: Nick Gould
* @parameter: _bIsVisible
* @return: void
********************/
void CCard::SetFlipped(bool _bIsFlipped)
{
	_bIsFlipped = m_bFlipped;
}