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


/***********************
* CCard: Contructor for Card class
* @author: Nick Gould
* @author: Callan Moore
* @return: void
********************/
CCard::CCard(void)
{
	m_bFlipped = false;;
}

/***********************
* ~CCard: Destructor for Card class
* @author: Nick Gould
* @return: void
********************/
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
	VALIDATE(CEntity::Initialise());
	SetSuit(_ESuit);
	SetNumber(_ECardnum);
	return true;
}

/***********************
* Draw: Calls the entity's sprite's draw function.
* @author: Nick Gould
* @return: void
********************/
void CCard::Draw()
{
	CEntity::Draw(m_bFlipped);
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
* IsFlipped: Returns whether the card is flipped or not
* @author: Nick Gould
* @return: bool: true if the card is flipped
********************/
bool CCard::IsFlipped()
{
	return m_bFlipped; 
}

/***********************
* SetSuit: Sets the suit of the card
* @author: Nick Gould
* @parameter: _eSuit: The new suit of the card
* @return: void
********************/
void CCard::SetSuit(ESuit _eSuit)
{
	m_eSuit = _eSuit;
	CEntity::SetSuit(_eSuit);
}

/***********************
* SetNumber: Sets the number of the card
* @author: Nick Gould
* @parameter: _eCardNum: The new Card value
* @return: void
********************/
void CCard::SetNumber(ECardNum _eCardNum)
{
	m_eCardNum = _eCardNum;
	CEntity::SetNumber(_eCardNum);
}

/***********************
* SetFlipped: Sets whether the card is flipped(value visible) or not.
* @author: Callan Moore
* @parameter: _bFlipped: The new value for Flipped
* @return: void
********************/
void CCard::SetFlipped (bool _bFlipped)
{
	m_bFlipped = _bFlipped;
}