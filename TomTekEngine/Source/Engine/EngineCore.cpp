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
#include "EngineCore.h"
#include "Engine/Window/EngineWindow.h"
#include "Engine/Rendering/EngineRenderer.h"

EngineCore::EngineCore( EngineWindow* window, EngineRenderer* renderer ) :
	m_Window( std::unique_ptr<EngineWindow>( window ) ),
	m_Renderer( std::unique_ptr<EngineRenderer>( renderer ))
{
	if ( m_Renderer.get() )
	{
		m_Renderer->Initialize( this );
	}

	m_EngineOnline = true;
}

bool EngineCore::IsEngineRunning()
{
	if ( !m_Window.get() ) { return false; }
	if ( !m_Renderer.get() ) { return false; }

	//If the window fails to poll events close the application
	if ( !m_Window->PollWindowEvents() ) { return false; }
	//If there is something wrong with the renderer close the application
	if ( !m_Renderer->IsOkay() ) { return false; }

	return m_EngineOnline;
}

void EngineCore::UpdateEngine()
{

}
