/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Entity.h
* Description : Header file for the Entity class
* Author :	Asma Shakil
*			Callan Moore
*			JC Fowles
*			Nick Gould
* Mail :	Asma.shakil@mediadesign.school.nz
*			Callan.moore@mediadesign.school.nz
*			Jc.fowles@mediadesign.school.nz	
*			Nick.gould@mediadesign.school.nz
*/

#pragma once

// Local Includes
#include "resource.h"
#include "Utilities.h"

#if !defined(__ENTITY_H__)
#define __ENTITY_H__



// Prototypes
class CSprite;

class CEntity
{
	// Member Functions
public:
	CEntity();
	virtual ~CEntity();
	virtual bool Initialise();
	virtual void Draw(bool _bFlipped);
	virtual void Process(float _fDeltaTick);
	void SetX(float _f);
	void SetY(float _f);
	float GetX() const;
	float GetY() const;
	float GetHeight() const;
	float GetWidth() const;
	void SetSuit(ESuit _eSuit);
	void SetNumber(ECardNum _eCardNum);
	void SetCardBack(ECardBack _eCardBacking);

private:
	// Disallowing copies
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);

	// Member Variables
protected:
	CSprite* m_pSprite;
	float m_fX;
	float m_fY;
};

#endif // __ENTITY_H__