/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Leave.cpp
* Description : Implementation file for the Level class
* Author :	Callan Moore
*			JC Fowles
*			Nick Gould
* Mail :	Callan.moore@mediadesign.school.nz	
*			JC.fowles@mediadesign.school.nz	
*			Nick.gould@mediadesign.school.nz	
*/



// This Include
#include "Level.h"

/***********************
* CLevel: Contructor for the Level class
* @author: Callan Moore
********************/
CLevel::CLevel()
{
	m_iWidth = 0;
	m_iHeight = 0;
}

/***********************
* ~CLevel: Destructor for the Level class
* @author: Callan Moore
********************/
CLevel::~CLevel()
{

}

/***********************
* Initialise: Initialise all the member variables of the Level class
* @author: Callan Moore
* @parameter: _iWidth: Width of the window for the level to cover
* @parameter: _iHeight: Height of the window for the level to cover
* @return: bool: Always returns true
********************/
bool CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	return true;
}

/***********************
* Draw: Draws all the entities that make up the level
* @author: Callan Moore
* @return: void
********************/
void CLevel::Draw()
{

}

/***********************
* Process: Process the changes to the Level for the current delta tick
* @author: Callan Moore
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CLevel::Process(float _fDeltaTick)
{

}