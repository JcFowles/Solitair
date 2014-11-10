/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : MouseStack.cpp
* Description : Implementation file for the Mouse Stack Class
* Author :	Callan Moore
*			Nick Gould
* Mail :	Callan.Moore@mediadesign.school.nz 
*			Nick.gould@mediadesign.school.nz
*/

#include "MouseStack.h"

/***********************
* CMouseStack: Contructor for Mouse Stack class
* @author: Callan Moore
* @return: void
********************/
CMouseStack::CMouseStack(void)
{
	m_pHeldCards = 0;
}

/***********************
* ~CMouseStack: Destructor for Mouse Stack class
* @author: Callan Moore
* @return: void
********************/
CMouseStack::~CMouseStack(void)
{
}

/***********************
* Initialise: Initialises the Mouse Stack member variables
* @author: Callan Moore
* @Parameters: _hInstance:  Handle to the specific instance of the running game
* @Parameters: _hWnd: Handle to the game window
* @Parameters: _iWidth: Width of the game window
* @Parameters: _iHeight: Height of the game window
* @return: void
********************/
bool CMouseStack::Initialise()
{
	m_pHeldCards = new vector<CCard*>;
	return true;
}

/***********************
* Draw: Draws the Mouse Stack to the screen
* @author: Callan Moore
* @return: void
********************/
void CMouseStack::Draw()
{
	if(m_pHeldCards->empty() != true)
	{
		for(unsigned int i = 0; i < m_pHeldCards->size() ; i++)
		{	
			if( i == 0)
			{
				(*m_pHeldCards)[i]->CEntity::SetX(m_fX);
				(*m_pHeldCards)[i]->CEntity::SetY(m_fY);
			}
			else
			{
				(*m_pHeldCards)[i]->CEntity::SetX( (*m_pHeldCards)[i-1]->GetX());
				(*m_pHeldCards)[i]->CEntity::SetY( ((*m_pHeldCards)[i-1]->GetY()) + 40);
			}

			(*m_pHeldCards)[i]->Draw();
		}
	}
}

/***********************
* Process: Process the MouseStack here
* @author: Callan Moore
* @parameter: _fDeltaTick: How long it takes to do the proccess
* @return: void
********************/
void CMouseStack::Process(float _fDeltaTick)
{

}

/***********************
* GetHeldCards: Retrieves the vector of held cards
* @author: Callan Moore
* @return: vector<CCard*>*: Pointer to the vector of held cards
********************/
vector<CCard*>* CMouseStack::GetHeldCards()
{
	return m_pHeldCards;
}

/***********************
* SetHeldCards: Sets the Mouse stacks vector of cards to the input 
* @author: Callan Moore
* @parameter: vector<CCard*>*: Vector of Cards to add to the Held Cards
* @return: void:
********************/
void CMouseStack::SetHeldCards(vector<CCard*>* _pCards)
{
	m_pHeldCards = _pCards;
}

/***********************
* SetMousePosition: Sets the X and Y coordinates of the MouseStack to the input Mouse coordinates
* @author: Callan Moore
* @parameter: _fMouseX: Mouse X coordinate
* @parameter: _fMouseY: Mouse Y coordinate
* @return: void
********************/
void CMouseStack::SetMousePosition(float _fMouseX, float _fMouseY)
{
	//CEntity::SetX(_fMouseX);
	//CEntity::SetY(_fMouseY);
	m_fX = _fMouseX;
	m_fY = _fMouseY;
}

/***********************
* GetMouseX: Retrieves the Mousestacks X position
* @author: Callan Moore
* @return: float: The Mouse X coordinate
********************/
float CMouseStack::GetMouseX()
{
	return m_fX;
}

/***********************
* GetMouseY: Retrieves the Mousestacks X position
* @author: Callan Moore
* @return: float: The Mouse Y coordinate
********************/
float CMouseStack::GetMouseY()
{
	return m_fY;
}
