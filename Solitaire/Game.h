/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
  
* (c) 2005 - 2014 Media Design School 
 
* File Name : Game.h 
* Description : Header file for the Game class
* Author :	Asma Shakil
*           Callan Moore
* 		    JC Fowles
*			Nick Gould
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*			Nick.gould@mediadesign.school.nz
*/

#pragma once
#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"
#include "BackBuffer.h"
#include "Deck.h"

// Types
// Constants

// Prototypes
class CBackBuffer;
class CPlayStack;

class CGame
{
	// Member Functions
public:
	~CGame();
	bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);
	void Draw();
	void Process(float _fDeltaTick);
	void ExecuteOneFrame();
	CBackBuffer* GetBackBuffer();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

	// Singleton Methods
	static CGame& GetInstance();
	static void DestroyInstance();
private:
	//Disallowing copies and extra constructions
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

	// Member Variables
protected:
	CClock* m_pClock;
	CBackBuffer* m_pBackBuffer;

	vector<CPlayStack*>* m_PlayStacks;
	CDeck* m_pDeck;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static CGame* s_pGame;

};
#endif // __GAME_H__