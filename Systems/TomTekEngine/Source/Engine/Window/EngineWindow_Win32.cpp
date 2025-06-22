/*
	MIT License

	Copyright (c) 2025 Liam Rousselle
	Copyright (c) 2025 TomTek

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	Script Author: Liam Rousselle
*/
#if defined (_WIN32)

#include <iostream>
#include "EngineWindow_Win32.h"

#include "Utilities/Helpers.hpp"

LRESULT CALLBACK WindowProcess( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( EXIT_SUCCESS );
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT paintStruct;
		HDC hdc = BeginPaint( hwnd, &paintStruct );
		EndPaint( hwnd, &paintStruct );
		return 0;
	}
	default:
		return DefWindowProc( hwnd, msg, wParam, lParam );
	}
}

EngineWindow_Win32::EngineWindow_Win32( std::string winName, uint32_t width, uint32_t height ) :
	EngineWindow( winName, width, height ),
	m_Msg( {} ),
	m_HInstance( GetModuleHandle( nullptr ) )
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProcess;
	wc.hInstance = m_HInstance;
	wc.lpszClassName = L"Win32_UNIDENTIFIED";
	wc.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	wc.hCursor = LoadCursor( nullptr, IDC_ARROW );

	if ( !RegisterClass( &wc ) )
	{
		throw std::exception( "Failed to register WNDCLASS EngineWindow_Win32::EngineWindow_Win32()" );
		return;
	}

	m_HWND = CreateWindow(
		wc.lpszClassName,
		L"TomTek Engine Win32",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_Width, m_Height,
		nullptr, nullptr, m_HInstance, nullptr
	);

	if ( !m_HWND )
	{
		throw std::exception( "Window attempt creation failed! EngineWindow_Win32::EngineWindow_Win32" );
		return;
	}

	ShowWindow( m_HWND, SW_SHOW );
	UpdateWindow( m_HWND );

	Helpers::Log( "Creation of EngineWindow_Win32 ok. %s", "HelloWorld" );
}

bool EngineWindow_Win32::PollWindowEvents()
{
	if ( !GetMessage( &m_Msg, nullptr, 0, 0 ) )
	{
		return false;
	}

	TranslateMessage( &m_Msg );
	DispatchMessage( &m_Msg );

	return true;
}

#endif //_WIN32