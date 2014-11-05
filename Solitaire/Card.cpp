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

#include "Card.h"


CCard::CCard(void)
{
	m_bIsVisible = false;
	m_eSuit = SUIT_DEFAULT;
	m_eCardNum = NUM_DEFAULT;
}


CCard::~CCard(void)
{

}

/***********************
* Initialise: Initialises the entity and creates its sprite (image)
* @author: Nick Gould
* @parameter:_ESuit: the enumerator card suit
* @parameter:_ECardnum: the enumerator card number
* @return: bool: always returns true
********************/
bool CCard::Initialise(ESuit _ESuit, ECardNum _ECardnum)
{
	return true;
//	m_iMaskID = IDB_MASK_CARD;
//
//	switch(_ESuit)
//	{
//	case(HEART):
//		{
//		switch(_ECardnum)
//			{
//			case(ACE):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_ACE;
//					break;
//				}
//			case(TWO):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_TWO;
//					break;
//				}
//			case(THREE):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_THREE;
//					break;
//				}
//			case(FOUR): 
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_FOUR;
//					break;
//				}
//			case(FIVE):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_FIVE;
//					break;
//				}
//			case(SIX):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_SIX;
//					break;
//				}
//			case(SEVEN):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_SEVEN;
//					break;
//				}
//			case(EIGHT):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_EIGHT;
//					break;
//				}
//			case(NINE):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_NINE;
//					break;
//				}
//			case(TEN):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_TEN;
//					break;
//				}
//			case(JACK):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_JACK;
//					break;
//				}
//			case(QUEEN):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_QUEEN;
//					break;
//				}
//			case(KING):
//				{
//					m_iSpriteID = IDB_SPRITE_HEART_KING;
//					break;
//				}
//			}
//		}
//	case(DIAMOND):
//		{
//		switch(_ECardnum)
//			{
//			case(ACE):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_ACE;
//					break;
//				}
//			case(TWO):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_TWO;
//					break;
//				}
//			case(THREE):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_THREE;
//					break;
//				}
//			case(FOUR): 
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_FOUR;
//					break;
//				}
//			case(FIVE):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_FIVE;
//					break;
//				}
//			case(SIX):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_SIX;
//					break;
//				}
//			case(SEVEN):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_SEVEN;
//					break;
//				}
//			case(EIGHT):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_EIGHT;
//					break;
//				}
//			case(NINE):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_NINE;
//					break;
//				}
//			case(TEN):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_TEN;
//					break;
//				}
//			case(JACK):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_JACK;
//					break;
//				}
//			case(QUEEN):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_QUEEN;
//					break;
//				}
//			case(KING):
//				{
//					m_iSpriteID = IDB_SPRITE_DIAMOND_KING;
//					break;
//				}
//			}
//
//		}
//	case(SPADE):
//		{
//		switch(_ECardnum)
//			{
//			case(ACE):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_ACE;
//					break;
//				}
//			case(TWO):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_TWO;
//					break;
//				}
//			case(THREE):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_THREE;
//					break;
//				}
//			case(FOUR): 
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_FOUR;
//					break;
//				}
//			case(FIVE):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_FIVE;
//					break;
//				}
//			case(SIX):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_SIX;
//					break;
//				}
//			case(SEVEN):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_SEVEN;
//					break;
//				}
//			case(EIGHT):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_EIGHT;
//					break;
//				}
//			case(NINE):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_NINE;
//					break;
//				}
//			case(TEN):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_TEN;
//					break;
//				}
//			case(JACK):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_JACK;
//					break;
//				}
//			case(QUEEN):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_QUEEN;
//					break;
//				}
//			case(KING):
//				{
//					m_iSpriteID = IDB_SPRITE_SPADE_KING;
//					break;
//				}
//			}
//
//		}
//	case(CLUB):
//		{
//		switch(_ECardnum)
//			{
//			case(ACE):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_ACE;
//					break;
//				}
//			case(TWO):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_TWO;
//					break;
//				}
//			case(THREE):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_THREE;
//					break;
//				}
//			case(FOUR): 
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_FOUR;
//					break;
//				}
//			case(FIVE):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_FIVE;
//					break;
//				}
//			case(SIX):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_SIX;
//					break;
//				}
//			case(SEVEN):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_SEVEN;
//					break;
//				}
//			case(EIGHT):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_EIGHT;
//					break;
//				}
//			case(NINE):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_NINE;
//					break;
//				}
//			case(TEN):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_TEN;
//					break;
//				}
//			case(JACK):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_JACK;
//					break;
//				}
//			case(QUEEN):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_QUEEN;
//					break;
//				}
//			case(KING):
//				{
//					m_iSpriteID = IDB_SPRITE_CLUB_KING;
//					break;
//				}
//			}
//
//		}
//	default:
//		{
//			m_iSpriteID = IDB_SPRITE_BLANK;
//		}
//
//
//
//
//	}
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
bool CCard::IsVisible()
{
	return m_bIsVisible; 
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
void CCard::SetVisible(bool _bIsVisible)
{
	_bIsVisible = m_bIsVisible;
}