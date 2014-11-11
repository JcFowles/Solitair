/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Sprite.cpp
* Description : Implementation file for the Sprite class
* Author :	Asma Shakil
*			Callan Moore
* Mail :	Asma.shakil@mediadesign.school.nz
*			Callan.moore@mediadesign.school.nz
*/

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

/***********************
* CSprite: Contructor for the Sprite class
* @author: Asma Shakil
********************/
CSprite::CSprite()	: m_iX(0)
					, m_iY(0)
{
	++s_iRefCount;
	m_iBackingID_Y = 4;
	m_eSuit = SUIT_DEFAULT;
	m_eNumber = ACE;
}

/***********************
* ~CSprite: Destructor for the Sprite class
* @author: Asma Shakil
********************/
CSprite::~CSprite()
{
	--s_iRefCount;
	if (s_iRefCount == 0)
	{
		DeleteObject(m_hSprite);
		DeleteObject(m_hMask);
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

/***********************
* Initialise: Initialises all the Sprite member variables
* @author: Asma Shakil
* @author: Callan Moore
* @return: bool: True if successful
********************/
bool CSprite::Initialise()
{
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();
	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}
	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SPRITE_CARD));
	VALIDATE(m_hSprite);
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_MASK_CARD));
	VALIDATE(m_hMask);
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);
	return (true);
}

/***********************
* Draw: Draws the sprite onto the backbuffer
* @author: Asma Shakil
* @author: Callan Moore
* @parameter: _bFlipped: Whethere the card has been flipped or not
* @return: void
********************/
void CSprite::Draw(bool _bFlipped)
{
	int iSpriteID_X, iSpriteID_Y;

	// If the Card is flipped show the front of the card
	if(_bFlipped)
	{
		iSpriteID_X = m_eNumber;
		iSpriteID_Y = m_eSuit;
	}
	// Show the current Card Backing choice
	else
	{
		iSpriteID_X =  m_eCardBack + 3;
		iSpriteID_Y = m_iBackingID_Y;
	}

	int iW = GetWidth();
	int iH = GetHeight();
	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();
	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);
	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);
	SelectObject(s_hSharedSpriteDC, m_hSprite);
	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, (iSpriteID_X * iW), (iSpriteID_Y * iH), SRCPAINT);
	SelectObject(s_hSharedSpriteDC, hOldObj);
}

/***********************
* Process: All Sprite actions are processed here
* @author: Asma Shakil
* @parameter: _fDeltaTick: How long it takes to do the process
* @return: void
********************/
void CSprite::Process(float _fDeltaTick)
{
}

/***********************
* GetWidth: Retrieves the width of the sprites bitmap image
* @author: Asma Shakil
* @author: Callan Moore
* @return: int: Width of the sprites bitmap image
********************/
int CSprite::GetWidth() const
{
	return (m_bitmapSprite.bmWidth / 13);	// The number of cards on the sprite sheet across
}

/***********************
* GetHeight: Retrieves the height of the sprites bitmap image
* @author: Asma Shakil
* @author: Callan Moore
* @return: int: Height of the sprites bitmap image
********************/
int CSprite::GetHeight() const
{
	return (m_bitmapSprite.bmHeight / 5);	// The number of cards on the sprite sheet down
}

/***********************
* GetX: Retrieves the X position of the sprite
* @author: Asma Shakil
* @return: int: X position of the sprite
********************/
int CSprite::GetX() const
{
	return (m_iX);
}

/***********************
* GetY: Retrieves the Y position of the sprite
* @author: Asma Shakil
* @return: int: Y position of the sprite
********************/
int CSprite::GetY() const
{
	return (m_iY);
}

/***********************
* SetX: Sets the X position of the sprite to the given value
* @author: Asma Shakil
* @parameter: _i: The new X position for the sprite
* @return: void
********************/
void CSprite::SetX(int _i)
{
	m_iX = _i;
}

/***********************
* SetY: Sets the Y position of the sprite to the given value
* @author: Asma Shakil
* @parameter: _i: The new Y position for the sprite
* @return: void
********************/
void CSprite::SetY(int _i)
{
	m_iY = _i;
}

/***********************
* TranslateRelative: Translates the sprite by the given X and Y values
* @author: Asma Shakil
* @parameter: _iX: The ammount to move the sprite by on the X axis
* @parameter: _iY: The ammount to move the sprite by on the Y axis
* @return: void
********************/
void CSprite::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

/***********************
* TranslateAbsolute: Moves the sprite to the given coordinates
* @author: Asma Shakil
* @parameter: _iX: The X coordinate to move the sprite to
* @parameter: _iY: The X coordinate to move the sprite to
* @return: void
********************/
void CSprite::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}

/***********************
* SetSuit: Sets the suit of the Sprite
* @author: Callan Moore
* @parameter: _eSuit: The new suit of the card
* @return: void
********************/
void CSprite::SetSuit(ESuit _eSuit)
{
	m_eSuit = _eSuit;
}

/***********************
* SetNumber: Sets the number of the Sprite
* @author: Callan Moore
* @parameter: _eCardNum: The new Card value
* @return: void
********************/
void CSprite::SetNumber(ECardNum _eCardNum)
{
	m_eNumber = _eCardNum;
}

/***********************
* SetCardBack: Sets the Card Backing for the Sprite
* @author: Callan Moore
* @parameter: _eCardBacking: Enum for the Card Backing
* @return: void
********************/
void CSprite::SetCardBack(ECardBack _eCardBacking)
{
	m_eCardBack = _eCardBacking;
}