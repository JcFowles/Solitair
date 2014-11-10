/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : Game.cpp 
* Description : Implementaion file for the Game Class
* Author :	Asma Shakil
*           Callan Moore
* 		    JC Fowles
*			Nick Gould
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*			Nick.gould@mediadesign.school.nz
*/

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;


/***********************
* CGame: Contructor, also initialises member variables to 0
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
CGame::CGame()	: m_pClock(0)
				, m_hApplicationInstance(0)
				, m_hMainWindow(0)
				, m_pBackBuffer(0)
				, m_pDeck(0)
				, m_PlayStacks(0)
				, m_WinStacks(0)
				, m_pMouseStack(0)
{
	/*
	for(int i = 0 ; i < 7; i++)
	{
		m_PlayStack[i] = new CPlayStack; 
	}*/
}

/***********************
* ~CGame: Destructor, deletes instance of the game
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
CGame::~CGame()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pClock;
	m_pClock = 0;

	while(!(m_PlayStacks->empty()))
	{
		m_PlayStacks->pop_back();
	}
	delete m_PlayStacks;
	m_PlayStacks = 0;
	/*for(int i = 0 ; i < 7; i++)
	{
		delete m_PlayStack[i] ; 
		m_PlayStack[i] = 0;
	}*/

	//delete m_pDeck;
	//m_pDeck = 0;
}

/***********************
* Initialise: Initialises the game member variables, starts the clock and backbuffer. Also sets the cursor to invisible
* @author: Asma Shakil
* @author: Jc Fowles
* @Parameters: _hInstance:  Handle to the specific instance of the running game
* @Parameters: _hWnd: Handle to the game window
* @Parameters: _iWidth: Width of the game window
* @Parameters: _iHeight: Height of the game window
* @return: void
********************/
bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	m_pClock = new CClock();
	VALIDATE(m_pClock ->Initialise());
	m_pClock->Process();
	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));
	//ShowCursor(false);
	
	

	//Card Stacks
	CPlayStack* tempStack;
	CWinStack* tempWinStack;
	m_PlayStacks = new vector<CPlayStack*>;
	m_WinStacks = new vector<CWinStack*>;
	m_pMouseStack = new CMouseStack();

	const float fkGap = 40.0f;
	const float fkYPlayStack = 380.0f;
	const float fkXPlayStack = 100.0f;
	const float fkCardWidth = 120.0f;
	const float fkPlusX = fkGap + fkCardWidth;

	for(int i = 0 ; i < 7; i++)
	{
		tempStack = new CPlayStack; 
		VALIDATE(tempStack->Initialise( ((i*fkPlusX)+fkXPlayStack), fkYPlayStack) );
		m_PlayStacks->push_back(tempStack);
	}

	//Win Stacks
	const float fkYWinStack = 130.0f;
	const float fkXWinStack = 580.0f;
	const float fkWInPlusX = fkGap + fkCardWidth;
	
	for(int i = 0 ; i < 4; i++)
	{
		tempWinStack = new CWinStack; 
		VALIDATE(tempWinStack->Initialise( ((i*fkWInPlusX)+fkXWinStack), fkYWinStack) );
		m_WinStacks->push_back(tempWinStack);
	}


	//The Deck
	const float fkYDeck = 130.0f;
	const float fkXDeck = 100.0f;
	

	m_pDeck = new CDeck();
	VALIDATE(m_pDeck->Initialise(fkXDeck, fkYDeck, m_PlayStacks));
	VALIDATE(m_pMouseStack->Initialise());


	return (true);
}

/***********************
* Draw: All the games drawing and redrawing will be done here, and drawing will be done to the backbuffer
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
void CGame::Draw()
{
	m_pBackBuffer->Clear();
	// Do all the game’s drawing here...
	
	m_pDeck->Draw();
	
	for(int i = 0; i < 7 ; i++)
	{
		(*m_PlayStacks)[i]->Draw();
	}

	for(int i = 0; i < 4 ; i++)
	{
		(*m_WinStacks)[i]->Draw();
	}

	m_pMouseStack->Draw();

	m_pBackBuffer->Present();
}

/***********************
* Process: All the game logic will be proccesed here
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @parameter: _fDeltaTick: How long it takes to do the proccess
* @return: void
********************/
void CGame::Process(float _fDeltaTick)
{
	// Process all the game’s logic here.
	for(unsigned int i = 0; i < m_PlayStacks->size() ; i++)
	{
		(*m_PlayStacks)[i]->Process(_fDeltaTick);
	}
}

/***********************
* ExecuteOneFrame: Executes a single frame for game process, 
* @author: Asma Shakil
* @return: void
********************/
void CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();
	Process(fDT);
	Draw();
	m_pClock->Process();
	Sleep(1);
}

/***********************
* GetInstance: Returns the singleton instance of the game, if it doesnt exist creates it.
* @author: Asma Shakil
* @return: CGame&: The current instance of the game
********************/
CGame& CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

/***********************
* DestroyInstance: Deletes the instance of the game. 
* @author: Asma Shakil
* @return: void
********************/
void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/***********************
* GetBackBuffer: Returns the current backbuffer to be used or updated. 
* @author: Asma Shakil
* @return: CBackBuffer*: The current backbuffer
********************/
CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

/***********************
* GetAppInstance: Returns the current instance of the programe/application
* @author: Asma Shakil
* @return: HINSTANCE: The current instance handler
********************/
HINSTANCE CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

/***********************
* GetWindow: Returns the current window handler
* @author: Asma Shakil
* @return: HWND: The current window handler
********************/
HWND CGame::GetWindow()
{
	return (m_hMainWindow);
}

/***********************
* GetWindow: Retrieves the Games Mouse stack pointer
* @author: Callan Moore
* @return: CMouseStack*: Pointer to the games mouse stack
********************/
CMouseStack* CGame::GetMouseStack()
{
	return m_pMouseStack;
}

/***********************
* MouseClick: Check to see if over a card
* @author: Callan Moore
* @author: Jc Fowles
* @author: Nick Gould
* @parameter: _fMouseX: The mouse X position
* @parameter: _fMouseY: The mouse Y position
* @return: void
********************/
void CGame::MouseClick(float _fMouseX, float _fMouseY)
{
	CCard* pPointedCard = 0;
	CPlayStack* pPointedStack = 0;
	CCard* pCurrentCard = 0; 
	CPlayStack* pCurrentStack = 0;

	if( m_pMouseStack->GetHeldCards()->empty() )
	{
		float fDeckX = m_pDeck->GetDrawPile()->back()->GetX();
		float fDeckY = m_pDeck->GetDrawPile()->back()->GetY();
		float fDeckHalfW = m_pDeck->GetDrawPile()->back()->GetWidth() / 2;
		float fDeckHalfH = m_pDeck->GetDrawPile()->back()->GetHeight() / 2;

		// Check if the mouse click was within the deck
		if ( (_fMouseX < fDeckX + fDeckHalfW && _fMouseX > fDeckX - fDeckHalfW) && (_fMouseY < fDeckY + fDeckHalfH && _fMouseY > fDeckY - fDeckHalfH) )
		{
			m_pDeck->Flip();
		}

		// Check if the mouse click was in the Pick up Pile area
		if(!(m_pDeck->GetPickUpPile()->empty()))
		{
			CCard* pPickUpTopCard = m_pDeck->GetPickUpPile()->back();
			float fPickX = pPickUpTopCard->GetX();
			float fPickY = pPickUpTopCard->GetY();
			float fPickHalfW = pPickUpTopCard->GetWidth() / 2;
			float fPickHalfH = pPickUpTopCard->GetHeight() / 2;

			// Take the top card if the click was inside the borders
			if ( (_fMouseX < fPickX + fPickHalfW && _fMouseX > fPickX - fPickHalfW) && (_fMouseY < fPickY + fPickHalfH && _fMouseY > fPickY - fPickHalfH) )
			{
				m_pMouseStack->GetHeldCards()->push_back(pPickUpTopCard);
				m_pDeck->GetPickUpPile()->pop_back();
			}
		}

		float fCardX;
		float fCardY;
		float fCardHalfW;
		float fCardHalfH;

		// Loop through all Play Stacks
		for(unsigned int i = 0; i < m_PlayStacks->size(); i++)
		{
			pCurrentStack = (*m_PlayStacks)[i];

			// Loop through all cards within current play stack
			for (unsigned int j = 1; j < pCurrentStack-> GetStack()->size(); j++)
			{
				pCurrentCard = (*(pCurrentStack->GetStack()))[j];

				fCardX = pCurrentCard->GetX();
				fCardY = pCurrentCard->GetY();
				fCardHalfW = pCurrentCard->GetWidth() / 2;
				fCardHalfH = pCurrentCard->GetHeight() / 2;

				// Check if mouse is within borders of current card
				if (	(_fMouseX < fCardX + fCardHalfW && _fMouseX > fCardX - fCardHalfW) 
					&&	(_fMouseY < fCardY + fCardHalfH && _fMouseY > fCardY - fCardHalfH) )
				{
					// Save current card and stack
					pPointedCard = pCurrentCard;
					pPointedStack = pCurrentStack;
				}
			}
		}

		// If the mouse was over a viable card when clicked
		if( pPointedCard != 0 && pPointedCard == pPointedStack->GetStack()->back())
		{
			// If the viable card is flipped then take it and add it to the MouseStack vector
			if( pPointedStack->GetStack()->back()->IsFlipped() )
			{
				m_pMouseStack->GetHeldCards()->push_back(pPointedCard);
				pPointedStack->GetStack()->pop_back();
			}
			// Card was front card of stack but not flipped yet so flip it only
			else
			{
				pPointedStack->GetStack()->back()->SetFlipped(true);
			}
		}
	}
	else
	{
		float fCardX;
		float fCardY;
		float fCardHalfW;
		float fCardHalfH;

		// Loop through all Play Stacks
		for(unsigned int i = 0; i < m_PlayStacks->size(); i++)
		{
			pCurrentStack = (*m_PlayStacks)[i];

			// Loop through all cards within current play stack
			for (unsigned int j = 1; j < pCurrentStack->GetStack()->size(); j++)
			{
				pCurrentCard = (*(pCurrentStack->GetStack()))[j];

				fCardX = pCurrentCard->GetX();
				fCardY = pCurrentCard->GetY();
				fCardHalfW = pCurrentCard->GetWidth() / 2;
				fCardHalfH = pCurrentCard->GetHeight() / 2;

				// Check if mouse is within borders of current card
				if (	(_fMouseX < fCardX + fCardHalfW && _fMouseX > fCardX - fCardHalfW) 
					&&	(_fMouseY < fCardY + fCardHalfH && _fMouseY > fCardY - fCardHalfH) )
				{
					// Save current card and stack
					pPointedCard = pCurrentCard;
					pPointedStack = pCurrentStack;
				}
			}
		}

		if( pPointedCard == pPointedStack->GetStack()->back())
		{
			if( pPointedStack->AddCards(m_pMouseStack->GetHeldCards()) )
			{
				while( !(m_pMouseStack->GetHeldCards()->empty()) )
				{
					m_pMouseStack->GetHeldCards()->pop_back();
				}
			}
		}

	}
}