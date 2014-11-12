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
	m_bWin = false;
	bCursorVisible = true;
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

	delete m_pDeck;
	m_pDeck = 0;

	// Delete all PlayStacks
	while( !(m_PlayStacks->empty()))
	{
		delete m_PlayStacks->back();
		m_PlayStacks->back() = 0;
		m_PlayStacks->pop_back();
	}
	delete m_PlayStacks;
	m_PlayStacks = 0;

	// Delete all WinStacks
	while( !(m_WinStacks->empty()))
	{
		delete m_WinStacks->back();
		m_WinStacks->back() = 0;
		m_WinStacks->pop_back();
	}
	delete m_WinStacks;
	m_WinStacks = 0;

	delete m_pMouseStack;
	m_pMouseStack = 0;
}

/***********************
* Initialise: Initialises the game member variables, starts the clock and backbuffer. Also sets the cursor to invisible
* @author: Asma Shakil
* @author: Jc Fowles
* @Parameters: _hInstance:  Handle to the specific instance of the running game
* @Parameters: _hWnd: Handle to the game window
* @Parameters: _iWidth: Width of the game window
* @Parameters: _iHeight: Height of the game window
* @return: bool: True if successful
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

	//Card Stacks
	CPlayStack* tempStack;
	CWinStack* tempWinStack;
	m_PlayStacks = new vector<CPlayStack*>;
	m_WinStacks = new vector<CWinStack*>;

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
	m_pMouseStack = new CMouseStack();
	VALIDATE(m_pMouseStack->Initialise());

	SetCardBack(DEFAULT);

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
	//WINNING CHECK
	m_bWin = true;
	for(unsigned int i = 0; i < m_WinStacks->size() ; i++)
	{
		
		if(!(*m_WinStacks)[i]->Complete())
		{
			m_bWin = false;
		}
	}
	
	if(m_bWin)
	{
		switch(MessageBoxA(m_hMainWindow, "You Have Won \n Would you like to play again" , "Winning", MB_YESNO))
		{
		case IDYES:
			{
				SendMessage(m_hMainWindow, WM_COMMAND, ID_GAME_NEWGAME, 0);
			}
			break;
		case IDNO:
			{
				PostQuitMessage(0);
			}
			break;
		}
	}
}

/***********************
* ExecuteOneFrame: Executes a single frame for game process, 
* @author: Asma Shakil
* @return: bool: true if game is won
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
* GetDeck: Returns a pointer to the games Deck
* @author: Jc Fowles
* @return: CDeck* : pointer to the games Deck
********************/
CDeck* CGame::GetDeck()
{
	return m_pDeck;
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
	int iPointedCardPosition = 0;
	CCard* pCurrentCard = 0; 
	CPlayStack* pCurrentStack = 0;
	CWinStack* pCurrentWinStack = 0;

	POINT ptMoveCursor;
	ptMoveCursor.x = 0;
	ptMoveCursor.y = 0;

	if( m_pMouseStack->GetHeldCards() == 0 )
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

		// Check if the mouse click was in the Pick up Pile area`	
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
				vector<CCard*>* pCardToTake = new vector<CCard*>;
				pCardToTake->push_back(pPickUpTopCard);
				m_pMouseStack->SetHeldCards(pCardToTake);
				m_pDeck->GetPickUpPile()->pop_back();

				m_pMouseStack->SetPrevDeck(m_pDeck);
				m_pMouseStack->SetPrevWinStack(0);
				m_pMouseStack->SetPrevPlayStack(0);
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
					iPointedCardPosition = j;

					m_pMouseStack->SetPrevDeck(0);
					m_pMouseStack->SetPrevWinStack(0);
					m_pMouseStack->SetPrevPlayStack(pPointedStack);
				}
			}
		}

		// If the mouse was over a viable Playstack card when clicked
		if( pPointedCard != 0)
		{
			// If the viable card is flipped then take it and add it to the MouseStack vector
			if( pPointedCard->IsFlipped() )
			{
				vector<CCard*>* pCardsToTake = pPointedStack->RemoveCards(iPointedCardPosition);

				m_pMouseStack->SetHeldCards(pCardsToTake);
				pCardsToTake = 0;
			}
			// Card was front card of stack but not flipped yet so flip it only
			else if( pPointedCard == pPointedStack->GetStack()->back())
			{
				pPointedStack->GetStack()->back()->SetFlipped(true);
			}
		}

		//loop through the win stacks
		for(unsigned int i = 0 ; i < m_WinStacks->size() ; i++)
		{
			pCurrentWinStack =  (*m_WinStacks)[i];

			for(unsigned int j = 1; j < pCurrentWinStack->GetCards()->size(); j++)
			{
				pCurrentCard = (*(pCurrentWinStack->GetCards()))[j];

				fCardX = pCurrentCard->GetX();
				fCardY = pCurrentCard->GetY();
				fCardHalfW = pCurrentCard->GetWidth() / 2;
				fCardHalfH = pCurrentCard->GetHeight() / 2;

				// Check if mouse is within borders of the playstack
				if (	(_fMouseX < fCardX + fCardHalfW && _fMouseX > fCardX - fCardHalfW) 
					&&	(_fMouseY < fCardY + fCardHalfH && _fMouseY > fCardY - fCardHalfH) )
				{
					vector<CCard*>* pCardToTake = new vector<CCard*>;
					pCardToTake->push_back(pCurrentCard);
					m_pMouseStack->SetHeldCards(pCardToTake);
					pCurrentWinStack->GetCards()->pop_back();

					m_pMouseStack->SetPrevDeck(0);
					m_pMouseStack->SetPrevWinStack(pCurrentWinStack);
					m_pMouseStack->SetPrevPlayStack(0);
					break;
				}
			}
		}
	}
	else // mouse stack has some cards in it
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
			for (unsigned int j = 0; j < pCurrentStack->GetStack()->size(); j++)
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

		// If the mouse was over a viable card when clicked check to see if cards can be added from the mouse stack to the clicked on area
		if(pPointedCard != 0)
		{
			if( pPointedCard == pPointedStack->GetStack()->back())
			{
				if( pPointedStack->AddCards(m_pMouseStack->GetHeldCards()) )
				{
					/*while( !(m_pMouseStack->GetHeldCards()->empty()) )
					{
						m_pMouseStack->GetHeldCards()->pop_back();
					}*/

					// Properly Delete the vector of held cards
					while( m_pMouseStack->GetHeldCards()->empty() == false)
					{
						//delete m_pMouseStack->GetHeldCards()->back(); 
						m_pMouseStack->GetHeldCards()->back() = 0;
						m_pMouseStack->GetHeldCards()->pop_back();
					}
					delete m_pMouseStack->GetHeldCards();
					m_pMouseStack->SetHeldCards(0);
				}
			}
		}
		else
		{
			// Loop through the win stacks
			for(unsigned int i = 0 ; i < m_WinStacks->size() ; i++)
			{
				pCurrentWinStack =  (*m_WinStacks)[i];
				CCard* pCardInWinStack = (*(pCurrentWinStack->GetCards()))[0];

				fCardX = pCardInWinStack->GetX();
				fCardY = pCardInWinStack->GetY();
				fCardHalfW = pCardInWinStack->GetWidth() / 2;
				fCardHalfH = pCardInWinStack->GetHeight() / 2;

				// Check if mouse is within borders of the Winstack
				if (	(_fMouseX < fCardX + fCardHalfW && _fMouseX > fCardX - fCardHalfW) 
					&&	(_fMouseY < fCardY + fCardHalfH && _fMouseY > fCardY - fCardHalfH) )
				{
					if((m_pMouseStack->GetHeldCards())->size() == 1)
					{
						// Check if adding a card is valid
						CCard* theCard = (*(m_pMouseStack->GetHeldCards()))[0];
					
						if(pCurrentWinStack->AddCard(theCard))
						{
							// Properly Delete the vector of held cards
							while( m_pMouseStack->GetHeldCards()->empty() == false)
							{
								//delete m_pMouseStack->GetHeldCards()->back(); 
								m_pMouseStack->GetHeldCards()->back() = 0;
								m_pMouseStack->GetHeldCards()->pop_back();
							}
							delete m_pMouseStack->GetHeldCards();
							m_pMouseStack->SetHeldCards(0);

							//m_pMouseStack->GetHeldCards()->pop_back();
						}
					}
				}
			}
		}

		if( m_pMouseStack->GetHeldCards() != 0)
		{
			//Returns Cards to the Deck if that was its last position before mouse stack
			if( m_pMouseStack->GetPrevDeck() != 0)
			{
				m_pMouseStack->GetPrevDeck()->GetPickUpPile()->push_back((m_pMouseStack->GetHeldCards()->back()));
				//m_pMouseStack->GetHeldCards()->pop_back();
			}
			// Returns Cards to the correct WinStack if that was its last position before mouse stack
			else if( m_pMouseStack->GetPrevWinStack() != 0)
			{
				m_pMouseStack->GetPrevWinStack()->AddCard(m_pMouseStack->GetHeldCards()->back());
				//m_pMouseStack->GetHeldCards()->pop_back();
			}
			// Returns Cards to the correct PlayStack if that was its last position before mouse stack
			else if( m_pMouseStack->GetPrevPlayStack() != 0)
			{
				m_pMouseStack->GetPrevPlayStack()->ReturnCards(m_pMouseStack->GetHeldCards());
				/*while( m_pMouseStack->GetHeldCards()->empty() == false)
				{
					m_pMouseStack->GetHeldCards()->pop_back();
				}*/
			}
			// Properly Delete the vector of held cards
			if( m_pMouseStack->GetHeldCards()->empty() == false)
			{
				//delete m_pMouseStack->GetHeldCards()->back(); 
				m_pMouseStack->GetHeldCards()->back() = 0;
				m_pMouseStack->GetHeldCards()->pop_back();
			}
			delete m_pMouseStack->GetHeldCards();
			m_pMouseStack->SetHeldCards(0);
		}
	}

	// Show cursor only when no cards are in mouse stack
	if( m_pMouseStack->GetHeldCards() != 0)
	{
		// Set cursor to false only if the cursor was true 
		if( bCursorVisible == true)
		{
			bCursorVisible = false;
			ShowCursor(false);
		}
	}
	else
	{
		// Set cursor to true only if the cursor was false 
		if( bCursorVisible == false)
		{
			bCursorVisible = true;
			ShowCursor(true);
		}
	}
}

/***********************
* SetCardBack: Sets the Card Backing for the game cards
* @author: Callan Moore
* @parameter: _eCardBacking: Enum for the Card Backing
* @return: void
********************/
void CGame::SetCardBack(ECardBack _eCardBacking)
{
	deque<CCard*>* pTempDeckCards = 0;
	pTempDeckCards = m_pDeck->GetDrawPile();

	// Set the Draw pile card backs
	for( unsigned int i = 0; i < pTempDeckCards->size(); i++)
	{
		(*pTempDeckCards)[i]->SetCardBack(_eCardBacking);
	}

	// Set the Pick up pile card backs
	pTempDeckCards = m_pDeck->GetPickUpPile();
	for( unsigned int i = 0; i < pTempDeckCards->size(); i++)
	{
		(*pTempDeckCards)[i]->SetCardBack(_eCardBacking);
	}

	// Set all Play Stacks card backs
	vector<CCard*>* pTempStackCards = 0;
	for( unsigned int i = 0; i < m_PlayStacks->size(); i++)
	{
		pTempStackCards = (*m_PlayStacks)[i]->GetStack();
		for( unsigned int j = 0; j < pTempStackCards->size(); j++)
		{
			(*pTempStackCards)[j]->SetCardBack(_eCardBacking);
		}
	}
}

/***********************
* SetCardFlipNum: Sets the Number of cards to flip from draw pile
* @author: Callan Moore
* @parameter: _iCardFlipNum: Number fo cards to flip
* @return: void
********************/
void CGame::SetCardFlipNum(int _iCardFlipNum)
{
	m_pDeck->setFlipNum(_iCardFlipNum);
}
