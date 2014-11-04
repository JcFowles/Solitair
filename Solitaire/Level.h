/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Level.h
* Description : Header file for the Level class
* Author :	Callan Moore
*			JC Fowles
*			Nick Gould
* Mail :	Callan.moore@mediadesign.school.nz	
*			JC.fowles@mediadesign.school.nz	
*			Nick.gould@mediadesign.school.nz	
*/

#pragma once

// Library Includes
#include <locale>
#include <codecvt>

// Local Includes
#include "Game.h"
#include "Utilities.h"
#include "backbuffer.h"

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

class CLevel
{
	// Member Functions
public:
	CLevel(void);
	~CLevel(void);
	virtual bool Initialise(int _iWidth, int _iHeight);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:
	//void ProcessCheckForWin();
	//void DrawScore();
	//void UpdateScoreText();

private:
	// Disallowing copies
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
private:
	int m_iWidth;
	int m_iHeight;

};

#endif // __LEVEL_H__
