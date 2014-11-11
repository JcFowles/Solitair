/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : main.cpp 
* Description : Implementaion file for the main application
* Author :	Asma Shakil
*			Callan Moore
* 			JC Fowles
*			Nick Gould
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*			Nick.gould@mediadesign.school.nz
*/

//Library Includes
#include <windows.h>
#include <windowsx.h>
#include <time.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "Utilities.h"
#define WINDOW_CLASS_NAME L"SOLITAIRE"

CGame& g_rGame = CGame::GetInstance();


/***********************
* WindowProc: Process the window 
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @author: Nick Gould
* @Parameter: _hWnd: Handle to the Window sending the message
* @Parameter: _uiMsg: The message ID being sent
* @Parameter: _wParam: Additional detail about the message being sent
* @Parameter: _lParam: Additional detail about the message being sent
* @return: LRESULT: The resulting value
********************/
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{

	switch (_uiMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return(0);
		};
		break;
	case WM_COMMAND:
		{
			switch(_wParam)
			{
			case (ID_HELP_ABOUT):
				{
					MessageBoxA(_hWnd, "Made by Callan, JC, and Nick" , "About", MB_OK);
				}
				break;

			case ID_GAME_EXIT: 
				{
					PostQuitMessage(0);
					return(0);
				};
				break;

			case ID_GAME_NEWGAME:
				{
					//getting the game instance
					HINSTANCE hInstance = (HINSTANCE)GetWindowLong(_hWnd, GWL_HINSTANCE);

					//width and height of the window
					int iWndWidth;
					int iWndHeight;
					
					//getting the width and height of the window
					RECT rect;
					if(GetWindowRect(_hWnd, &rect))
					{
					  iWndWidth = rect.right - rect.left;
					  iWndHeight = rect.bottom - rect.top;
					}

					//destroy and recreate the game
					(&g_rGame)->DestroyInstance();
					g_rGame.GetInstance();

					if (!(g_rGame).Initialise(hInstance, _hWnd, iWndWidth, iWndHeight))
					{
						// Failed
						return (0);
					}


				}
				break;
			} // End Switch
			
		}
		break;
	case WM_LBUTTONDOWN:
		{

			float fMouseX = LOWORD(_lParam);
			float fMouseY = HIWORD(_lParam);

			CGame::GetInstance().GetMouseStack()->SetMousePosition(fMouseX,  fMouseY);
			CGame::GetInstance().MouseClick(fMouseX, fMouseY);
		}
	case WM_MOUSEMOVE:
		{
			//g_fMouseX = LOWORD(_lParam);
			//g_fMouseY = HIWORD(_lParam);

			float fMouseX = LOWORD(_lParam);
			float fMouseY = HIWORD(_lParam);

			CGame::GetInstance().GetMouseStack()->SetMousePosition(fMouseX,  fMouseY);
			CGame::GetInstance().Draw();
		}

	break;
	default:break;
	}



	if(g_rGame.HasWon())
	{
		switch(MessageBoxA(_hWnd, "You Have Won \n Would you like to play again" , "Winning", MB_YESNO))
		{
		case IDYES:
			{
				//getting the game instance
				HINSTANCE hInstance = (HINSTANCE)GetWindowLong(_hWnd, GWL_HINSTANCE);

				//width and height of the window
				int iWndWidth;
				int iWndHeight;
					
				//getting the width and height of the window
				RECT rect;
				if(GetWindowRect(_hWnd, &rect))
				{
					iWndWidth = rect.right - rect.left;
					iWndHeight = rect.bottom - rect.top;
				}

				//destroy and recreate the game
				(&g_rGame)->DestroyInstance();
				g_rGame.GetInstance();

				if (!(g_rGame).Initialise(hInstance, _hWnd, iWndWidth, iWndHeight))
				{
					// Failed
					return (0);
				}

			}
			break;
		case IDNO:
			{
				PostQuitMessage(0);
				return(0);
			}

		}
	}



	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

/***********************
* CreateAndRegisterWindow: Create and register the window of the application 
* @author: Asma Shakil
* @Parameter: _hInstance: Instance handler for the application
* @Parameter: _iWidth: Width of the window
* @Parameter: _iHeight: Height of the window
* @Parameter: _pcTitle: Title of the window
* @return: HWND: Handle to the window
********************/
HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
	WNDCLASSEX winclass;
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	HMENU hMenu = LoadMenu( _hInstance, MAKEINTRESOURCE(IDR_SOLITAIRE));

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(	NULL,
							WINDOW_CLASS_NAME,
							_pcTitle,
							WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
							CW_USEDEFAULT, CW_USEDEFAULT,
							_iWidth, _iHeight,
							NULL,
							hMenu,
							_hInstance,
							NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}
	return (hwnd);
}

/***********************
* WinMain: Program starts here 
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @Parameter: _hInstance: Instance handle that Windows generates for your application
* @Parameter: _hPrevInstance: Tracker for the previous instance for the application
* @Parameter: _lpCmdline: Wide char string that contains the passed in arguments 
* @Parameter: _iCmdshow: Integer passed in during launch, indicating how the application window is opened
* @return: int: Program ends here
********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	const int kiWidth = 1160;
	const int kiHeight = 1040;
	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Solitaire");
	//CGame& rGame = CGame::GetInstance();


	std::srand ( unsigned ( time(0) ) );

	if (!g_rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	{
		// Failed
		return (0);
	}
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//rGame.GetInstance();
			g_rGame.ExecuteOneFrame();
		}
	}
	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}

