/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
  
* (c) 2005 - 2014 Media Design School 
  
* File Name : Clock.h 
* Description : Header file for the Clock class
* Author :	Asma Shakil
* Mail :	Asma.Shakil@mediadesign.school.nz 
*/

#pragma once

// Library Includes
#include <windows.h>

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Prototypes
class CClock
{
	// Member Functions
public:
	CClock();
	~CClock();

	bool Initialise();
	void Process();

	// Getters
	float GetDeltaTick();

private:
	//Disallowing copies
	CClock(const CClock& _kr);
	CClock& operator= (const CClock& _kr);

	// Member Variables
protected:
	float m_fTimeElapsed;
	float m_fDeltaTime;
	float m_fLastTime;
	float m_fCurrentTime;
};

#endif // __CLOCK_H__